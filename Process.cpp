#include "Process.hpp"

Process::~Process()
{
	delete[] accelerations;
}


Process::Process(const int rank) noexcept
	: accelerations{ nullptr }, firstAtom{ nullptr }, lastAtom{ nullptr }, rank{ rank }
{
}

std::size_t Process::getAtomNumber() const noexcept
{
	std::size_t result = 0;
	if (firstAtom != nullptr && lastAtom != nullptr)
		result = lastAtom - firstAtom + 1;
	return result;
}

void Process::changeAccelerationsSize()
{
	delete[] accelerations;
	accelerations = nullptr;
	if (firstAtom != nullptr && lastAtom != nullptr)
	{
		std::size_t number = getAccelerationsSize();
		accelerations = new double[number];
	}
}

int Process::getRank() const noexcept { return rank; }

void Process::preparationForDataExchange()
{
	size_t atomNumber = getAtomNumber();
	if (getAccelerationsSize() < atomNumber * DIMENSIONAL_NUMBER)
		changeAccelerationsSize();

	Vector acceleration;
	for (size_t index = 0; index < atomNumber; ++index)
	{
		acceleration = (firstAtom + index)->getAcceleration();
		for (Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
			accelerations[index * DIMENSIONAL_NUMBER + i] = acceleration[i];
	}
}

double* Process::getAccelerationsPointer() noexcept { return accelerations; }

size_t Process::getAccelerationsSize() const noexcept { return getAtomNumber() * DIMENSIONAL_NUMBER; }

void Process::setAtoms(Atom& first, Atom& last) noexcept
{
	firstAtom = &first;
	lastAtom = &last;
	changeAccelerationsSize();
}
