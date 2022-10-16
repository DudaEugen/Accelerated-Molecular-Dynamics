#include <algorithm>
#include <exception>
#include "mpi.h"
#include "Parallel/MPI/Processes.hpp"
#include "IndexedZip.hpp"
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

void md::Processes::broadcast(std::vector<double>& data) const
{
	MPI_Bcast(static_cast<void*>(data.data()), data.size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
}

void md::Processes::gatherToAll(std::vector<double>& data, std::vector<int>& sendCounts) const
{
	if (sendCounts.size() != getCount())
		throw std::runtime_error("Incorrect sendCounts");
	
	std::vector<int> offsets = std::vector<int>(count);
	std::size_t summOffset = 0;
	for (auto [count, offset]: utils::zip::Zip(sendCounts, offsets))
	{
		offset = summOffset;
		summOffset += count;
	}

	auto sendBuf = std::vector<double>(sendCounts[rank]);
	std::copy(
		data.begin() + offsets[rank],
		(rank == count - 1) ? data.end() : (data.begin() + offsets[rank + 1]),
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

void md::Processes::setVelocities(std::vector<Atom>& atoms) const
{
	auto velocities = std::vector<double>();
	for (auto& atom: atoms)
	{
		for (auto proj: atom.getVelocity())
		{
			velocities.push_back(proj);
		}
	}
	broadcast(velocities);
	for (auto [index, atom]: utils::zip::IndexedZip(atoms))
	{
		Vector velocity;
		for (std::uint8_t projIndex = 0; projIndex < kDimensionalNumber; ++projIndex)
		{
			velocity[projIndex] = velocities[index*kDimensionalNumber + projIndex];
		}
		atom.setVelocity(velocity);
	}
}

void md::Processes::exchangeAccelerations(std::vector<Atom*>& atoms, const std::vector<int>& sendCounts) const
{

	std::vector<int> redefinedSendCounts{sendCounts};
	for (auto& count: redefinedSendCounts)
	{
		count *= kDimensionalNumber;
	}

	auto accelerations = std::vector<double>();
	for (auto atom: atoms)
	{
		for (auto proj: atom->getAcceleration())
		{
			accelerations.push_back(proj);
		}
	}
	gatherToAll(accelerations, redefinedSendCounts);
	for (auto [index, atom]: utils::zip::IndexedZip(std::as_const(atoms)))
	{
		Vector acceleration;
		for (std::uint8_t projIndex = 0; projIndex < kDimensionalNumber; ++projIndex)
		{
			acceleration[projIndex] = accelerations[index*kDimensionalNumber + projIndex];
		}
		atom->setAcceleration(acceleration);
	}
}
