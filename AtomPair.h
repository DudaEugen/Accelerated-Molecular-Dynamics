#pragma once
#ifndef TAHD_ATOM_PAIR_H
#define TAHD_ATOM_PAIR_H

#include "Atom.h"
#include "BorderConditions.h"

/*AtomPair class is replying for computing and storing: an distances between Atoms and differences of Atoms coordinates;
it is known Atom Pair: atoms contain in same stream or in different*/
class AtomPair
{
private:
	Vector dProjections;
	Atom* atomPair[2];
	double distance;
	bool isUsingBorderConditions;						//method computeDistance() use border conditions if true
	bool isAtomsFromSameStream;
	static BorderConditions* borderConditions;

public:
	AtomPair(Atom* first, Atom* second, const bool isUsingBorderConditions = false);
	AtomPair(Atom* first, Atom* second, const double d, const Vector deltaCoordinates, const bool isUsingBorderConditions = false);
	static void setBorderConditions(BorderConditions* borderConditions);
	Atom& getFirst() const;
	Atom& getSecond() const;
	double getDistance() const;
	Vector::ConstVectorPass getDistanceProjections() const;
	bool getIsAtomsFromSameStream() const;
	void setIsUsingBorderConditions(const bool isUsing);
	void setIsAtomsFromSameStream(const bool isSame);
	double computeDistance();
};

#endif	//TAHD_ATOM_PAIR_H
