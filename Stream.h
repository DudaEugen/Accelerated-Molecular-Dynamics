#pragma once
#ifndef TAHD_STREAM_H
#define TAHD_STREAM_H

#include "Atom.h"
#include "AtomGroup.h"

class Stream
{
private:
	int rank;
	double* accelerations;	// vector of projections of accelerations for data exchange by MPI
	size_t accelerationsSize;
public:
	AtomGroup atoms;
private:
	~Stream();
	void changeAccelerationsSize();	//change size of accelerations array
public:
	Stream(const int rank, const size_t atomsNumber = 0);
	int getRank() const noexcept;
	void preparationForDataExchange();
	double* getAccelerationsPointer() noexcept;		//get  vector of accelerations for MPI
	size_t getAccelerationsNumber() const noexcept; // get number of elements, that have acceleration of atoms
};

#endif	//TAHD_STREAM_H
