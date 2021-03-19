#include "Parallel/MPI/Process.hpp"

md::Process::~Process()
{
	delete[] accelerations;
}


md::Process::Process(const int rank) noexcept
	: accelerations{ nullptr }, firstAtom{ nullptr }, lastAtom{ nullptr }, rank{ rank }
{
}

std::size_t md::Process::getAtomNumber() const noexcept
{
	std::size_t result = 0;
	if (firstAtom != nullptr && lastAtom != nullptr)
		result = lastAtom - firstAtom + 1;
	return result;
}

void md::Process::changeAccelerationsSize()
{
	delete[] accelerations;
	accelerations = nullptr;
	if (firstAtom != nullptr && lastAtom != nullptr)
	{
		std::size_t number = getAccelerationsSize();
		accelerations = new double[number];
	}
}

int md::Process::getRank() const noexcept { return rank; }

void md::Process::preparationForDataExchange()
{
	size_t atomNumber = getAtomNumber();
	if (getAccelerationsSize() < atomNumber * kDimensionalNumber)
		changeAccelerationsSize();

	Vector acceleration;
	for (size_t index = 0; index < atomNumber; ++index)
	{
		acceleration = (firstAtom + index)->getAcceleration();
		for (Vector::projection_index i = 0; i < kDimensionalNumber; ++i)
			accelerations[index * kDimensionalNumber + i] = acceleration[i];
	}
}

double* md::Process::getAccelerationsPointer() noexcept { return accelerations; }

size_t md::Process::getAccelerationsSize() const noexcept { return getAtomNumber() * kDimensionalNumber; }

void md::Process::setAtoms(Atom& first, Atom& last) noexcept
{
	firstAtom = &first;
	lastAtom = &last;
	changeAccelerationsSize();
}
