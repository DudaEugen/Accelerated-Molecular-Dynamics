#pragma once
#ifndef TAHD_STREAM_H
#define TAHD_STREAM_H

#include "Atom.hpp"

class Process
{
private:
	double* accelerations;	// vector of projections of accelerations for data exchange by MPI
	Atom* firstAtom;
	Atom* lastAtom;
	int rank;
public:

	~Process();
private:
	std::size_t getAtomNumber() const noexcept;
	void changeAccelerationsSize();	//change size of accelerations array
public:
	Process(const int rank) noexcept;
	int getRank() const noexcept;
	void preparationForDataExchange();
	double* getAccelerationsPointer() noexcept;		//get  vector of accelerations for MPI
	size_t getAccelerationsSize() const noexcept; // get number of elements, that have acceleration of atoms
	void setAtoms(Atom& firstAtom, Atom& lastAtom) noexcept;
};

#endif	//TAHD_STREAM_H
