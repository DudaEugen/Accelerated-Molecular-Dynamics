#include "Stream.h"

Stream::~Stream()
{
	delete[] accelerations;
}


Stream::Stream(const int rank, const size_t atomsNumber) 
	: rank{ rank }, atoms{ atomsNumber }, accelerations{ nullptr }, accelerationsSize{ atomsNumber * DIMENSIONAL_NUMBER }
{
	accelerations = new double[atomsNumber * DIMENSIONAL_NUMBER];
}

void Stream::changeAccelerationsSize()
{
	delete[] accelerations;
	accelerations = new double[atoms.getAtomNumber() * DIMENSIONAL_NUMBER];
}

int Stream::getRank() const { return rank; }

void Stream::preparationForDataExchange()
{
	size_t atomNumber = atoms.getAtomNumber();
	if (accelerationsSize < atomNumber * DIMENSIONAL_NUMBER)
	{
		changeAccelerationsSize();
	}

	ProjectionTuple acceleration;
	for (size_t atomIndex = 0; atomIndex < atomNumber; ++atomIndex)
	{
		acceleration = atoms[atomIndex].getAcceleration();
		for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		{
			accelerations[atomIndex * DIMENSIONAL_NUMBER + i] = acceleration[i];
		}
	}
}

double* Stream::getAccelerationsPointer() { return accelerations; }

size_t Stream::getAccelerationsNumber() const { return atoms.getAtomNumber() * DIMENSIONAL_NUMBER; }
