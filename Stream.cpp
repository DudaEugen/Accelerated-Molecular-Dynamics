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

	Vector acceleration;
	for (size_t atomIndex = 0; atomIndex < atomNumber; ++atomIndex)
	{
		acceleration = atoms[atomIndex].getAcceleration();
#if DIMENSIONAL_NUMBER == 3
		accelerations[atomIndex * DIMENSIONAL_NUMBER + 0] = acceleration[0];
		accelerations[atomIndex * DIMENSIONAL_NUMBER + 1] = acceleration[1];
		accelerations[atomIndex * DIMENSIONAL_NUMBER + 2] = acceleration[2];
#elif DIMENSIONAL_NUMBER == 2
		accelerations[atomIndex * DIMENSIONAL_NUMBER + 0] = acceleration[0];
		accelerations[atomIndex * DIMENSIONAL_NUMBER + 1] = acceleration[1];
#else
		for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		{
			accelerations[atomIndex * DIMENSIONAL_NUMBER + i] = acceleration[i];
		}
#endif
	}
}

double* Stream::getAccelerationsPointer() { return accelerations; }

size_t Stream::getAccelerationsNumber() const { return atoms.getAtomNumber() * DIMENSIONAL_NUMBER; }
