#pragma once
#ifndef TAHD_ATOM_PAIR_H
#define TAHD_ATOM_PAIR_H

#include "Atom.h"

/*AtomPair class is replying for computing and storing: an distances between Atoms and differences of Atoms coordinates*/
class AtomPair
{
private:
	Atom* atomPair[2];
	double distance;
	ProjectionTuple dProjections;
public:
	AtomPair(Atom* first, Atom* second);
	AtomPair(Atom* first, Atom* second, const double d, const ProjectionTuple& deltaCoordinate);
	void computeDistance();					//refresh distance and dProjections fields
	static double computeDistance(const Atom* first, const Atom* second);
	static double computeDistance(const Atom* first, const Atom* second, ProjectionTuple& projections);	//write to projections difference of coordinates first and second
};

#endif	//TAHD_ATOM_PAIR_H
