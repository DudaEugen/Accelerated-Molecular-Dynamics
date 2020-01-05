#pragma once
#ifndef TAHD_ATOM_PAIR_H
#define TAHD_ATOM_PAIR_H

#include "Atom.h"
#include "BorderConditions.h"

/*AtomPair class is replying for computing and storing: an distances between Atoms and differences of Atoms coordinates*/
class AtomPair
{
private:
	Atom* atomPair[2];
	double distance;
	Vector dProjections;
	static BorderConditions* borderConditions;
	bool isUsingBorderConditions;						//method computeDistance() use border conditions if true

	void computeDistance_ignoringBorderConditions();	//refresh distance and dProjections fields ignoring border conditions
	void computeDistance_usingBorderConditions();		//refresh distance and dProjections fields using border conditions
public:
	AtomPair(Atom* first, Atom* second, const bool isUsingBorderConditions = false);
	AtomPair(Atom* first, Atom* second, const double d, const Vector& deltaCoordinate, const bool isUsingBorderConditions = false);
	static void setBorderConditions(BorderConditions* borderConditions);
	double getDistance() const;
	double getDistanceProjection(const projection_index index) const;
	void computeDistance();
	static double computeDistance(const Atom* first, const Atom* second, const bool isUsingBorderConditions = false);
	//write to projections difference of coordinates first and second
	static double computeDistance(const Atom* first, const Atom* second, Vector& projections, const bool isUsingBorderConditions = false);
};

#endif	//TAHD_ATOM_PAIR_H
