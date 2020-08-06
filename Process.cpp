#include "Process.h"

Process::~Process()
{
	delete[] accelerations;
}


Process::Process(const int rank, const size_t atomsNumber) 
	: rank{ rank }, atoms{ atomsNumber }, accelerations{ nullptr }, accelerationsSize{ atomsNumber * DIMENSIONAL_NUMBER }
{
	accelerations = new double[atomsNumber * DIMENSIONAL_NUMBER];
}

void Process::changeAccelerationsSize()
{
	delete[] accelerations;
	accelerations = new double[atoms.getAtomNumber() * DIMENSIONAL_NUMBER];
}

int Process::getRank() const noexcept { return rank; }

void Process::preparationForDataExchange()
{
	size_t atomNumber = atoms.getAtomNumber();
	if (accelerationsSize < atomNumber * DIMENSIONAL_NUMBER)
		changeAccelerationsSize();

	Vector acceleration;
	for (size_t atomIndex = 0; atomIndex < atomNumber; ++atomIndex)
		for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		{
			accelerations[atomIndex * DIMENSIONAL_NUMBER + i] = acceleration[i];
		}
}

double* Process::getAccelerationsPointer() noexcept { return accelerations; }

size_t Process::getAccelerationsNumber() const noexcept { return atoms.getAtomNumber() * DIMENSIONAL_NUMBER; }
