#include <algorithm>
#include <exception>
#include <numeric>
#include "mpi.h"
#include "Parallel/MPI/Processes.hpp"
#include "Zip.hpp"

md::Processes::Processes()
	: count{ defineCount() }, rank{ defineRank() }
{
}

int md::Processes::defineCount()
{
	int count;
	MPI_Comm_size(MPI_COMM_WORLD, &count);
	return count;
}

int md::Processes::defineRank()
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	return rank;
}

unsigned md::Processes::getCount() const noexcept
{
	return static_cast<unsigned>(count);
}

unsigned md::Processes::getRank() const noexcept
{
	return static_cast<unsigned>(rank);
}

void md::Processes::broadcast(std::vector<double>& data, unsigned root) const
{
	MPI_Bcast(static_cast<void*>(data.data()), data.size(), MPI_DOUBLE, root, MPI_COMM_WORLD);
}

void md::Processes::gatherToAll(std::vector<double>& data, const std::vector<int>& sendCounts) const
{
	if (sendCounts.size() != getCount())
		throw std::runtime_error("Incorrect sendCounts");
	if (static_cast<std::size_t>(std::reduce(sendCounts.cbegin(), sendCounts.cend(), 0)) != data.size())
		throw std::runtime_error("Incorrect sendCounts or data size");

	std::vector<int> offsets = std::vector<int>(count);
	std::size_t summOffset = 0;
	for (auto [sendCount, offset]: utils::zip::Zip(sendCounts, offsets))
	{
		offset = summOffset;
		summOffset += sendCount;
	}

	auto sendBuf = std::vector<double>(sendCounts[rank]);
	std::copy(
		data.cbegin() + offsets[rank],
		(rank == count - 1) ? data.end() : (data.cbegin() + offsets[rank + 1]),
		sendBuf.begin()
	);

	MPI_Allgatherv(
		static_cast<void*>(sendBuf.data()),
		sendCounts[rank],
		MPI_DOUBLE,
		static_cast<void*>(data.data()),
		sendCounts.data(),
		offsets.data(),
		MPI_DOUBLE,
		MPI_COMM_WORLD
	);
}

void md::Processes::broadcast(std::vector<Vector>& data, unsigned root) const
{
	auto values = convertVectorsToValues(data);
	broadcast(values, root);

	auto result = convertValuesToVectors(values);
	std::copy(result.cbegin(), result.cend(), data.begin());
}

void md::Processes::gatherToAll(std::vector<Vector>& data, const std::vector<int>& sendCounts) const
{
	std::vector<int> redefinedSendCounts{sendCounts};
	std::transform(
		sendCounts.cbegin(),
		sendCounts.cend(),
		redefinedSendCounts.begin(),
		[](int count){ return count * kDimensionalNumber; }
	);

	auto values = convertVectorsToValues(data);
	gatherToAll(values, redefinedSendCounts);

	auto result = convertValuesToVectors(values);
	std::copy(result.cbegin(), result.cend(), data.begin());
}

std::vector<double> md::Processes::convertVectorsToValues(const std::vector<md::Vector> vectors) const
{
	std::vector<double> result;
	result.reserve(vectors.size() * kDimensionalNumber);
	for (md::Vector::ConstPass vector: vectors)
	{
		for (double value: vector)
		{
			result.push_back(value);
		}
	}
	return result;
}

std::vector<md::Vector> md::Processes::convertValuesToVectors(const std::vector<double> values) const
{
	std::vector<Vector> result;
	std::size_t vectorsCount = values.size() / kDimensionalNumber;
	result.reserve(vectorsCount);
	for (std::size_t index = 0; index < vectorsCount; ++index)
	{
		Vector vector;
		for (std::uint8_t projIndex = 0; projIndex < kDimensionalNumber; ++projIndex)
		{
			vector[projIndex] = values[index*kDimensionalNumber + projIndex];
		}
		result.push_back(vector);
	}
	return result;
}

void md::Processes::setVelocities(std::vector<Atom>& atoms, unsigned root) const
{
	std::vector<Vector> velocities(atoms.size());
	std::transform(
		atoms.cbegin(),
		atoms.cend(),
		velocities.begin(),
		[](const Atom& atom){ return atom.getVelocity(); }
	);
	broadcast(velocities, root);
	for (auto [atom, velocity]: utils::zip::Zip(atoms, std::as_const(velocities)))
	{
		atom.setVelocity(velocity);
	}
}

void md::Processes::exchangeAccelerations(std::vector<Atom*>& atoms, const std::vector<int>& sendCounts) const
{
	std::vector<Vector> accelerations(atoms.size());
	std::transform(
		atoms.begin(),
		atoms.end(),
		accelerations.begin(),
		[](Atom const * const atom){ return atom->getAcceleration(); }
	);
	gatherToAll(accelerations, sendCounts);
	for (auto [atom, acceleration]: utils::zip::Zip(atoms, std::as_const(accelerations)))
	{
		atom->setAcceleration(acceleration);
	}
}
