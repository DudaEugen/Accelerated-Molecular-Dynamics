#include "Stream.h"

Stream::~Stream()
{
	delete[] accelerations;
}


Stream::Stream(const int rank, const size_t atomsNumber) 
	: rank{ rank }, atoms{}, accelerations{ nullptr }, accelerationsSize{ atomsNumber * DIMENSIONAL_NUMBER }
{
	atoms.reserve(atomsNumber);
	accelerations = new double[atomsNumber * DIMENSIONAL_NUMBER];
}

void Stream::changeAccelerationsSize()
{
	delete[] accelerations;
	accelerations = new double[atoms.size() * DIMENSIONAL_NUMBER];
}

int Stream::getRank() const { return rank; }

void Stream::addAtom(Atom* atom) 
{ 
	atoms.push_back(atom);
}

size_t Stream::getAtomNumber() const { return atoms.size(); }

Atom& Stream::getAtom(const size_t index) { return *atoms[index]; }

void Stream::preparationForDataExchange()
{
	if (accelerationsSize < atoms.size() * DIMENSIONAL_NUMBER) 
	{
		changeAccelerationsSize();
	}

	ProjectionTuple acceleration;
	for (size_t atomIndex = 0; atomIndex < atoms.size(); ++atomIndex)
	{
		acceleration = atoms[atomIndex]->getAcceleration();
		for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		{
			accelerations[atomIndex * DIMENSIONAL_NUMBER + i] = acceleration[i];
		}
	}
}

double* Stream::getAccelerationsPointer() { return accelerations; }

size_t Stream::getAccelerationsNumber() const { return atoms.size() * DIMENSIONAL_NUMBER; }
