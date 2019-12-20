#pragma once
#ifndef TAHD_STREAM_H
#define TAHD_STREAM_H

#include "Atom.h"
#include <vector>

class Stream
{
private:
	int rank;
	std::vector<Atom*> atoms;
	double* accelerations;	// vector of projections of accelerations for data exchange by MPI
	size_t accelerationsSize;

	~Stream();
	void changeAccelerationsSize();	//change size of accelerations array
public:
	Stream(const int rank, const size_t atomsNumber = 0);
	int getRank() const;
	void addAtom(Atom* atom);
	size_t getAtomNumber() const;
	Atom& getAtom(const size_t index);
	void preparationForDataExchange();
	double* getAccelerationsPointer();		//get  vector of accelerations for MPI
	size_t getAccelerationsNumber() const; // get number of elements, that have acceleration of atoms
};

#endif	//TAHD_STREAM_H
