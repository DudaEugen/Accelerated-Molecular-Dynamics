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
	AtomPair(Atom* first, Atom* second, const bool isUsingBorderConditions = false) noexcept;
	AtomPair(Atom* first, Atom* second, const double d, const Vector deltaCoordinates, const bool isUsingBorderConditions = false) noexcept;
	static void setBorderConditions(BorderConditions* borderConditions) noexcept;
	Atom& getFirst() const noexcept;
	Atom& getSecond() const noexcept;
	double getDistance() const noexcept;
	Vector::ConstVectorPass getDistanceProjections() const noexcept;
	bool getIsAtomsFromSameStream() const noexcept;
	void setIsUsingBorderConditions(const bool isUsing) noexcept;
	void setIsAtomsFromSameStream(const bool isSame) noexcept;
	double computeDistance() noexcept;
};

#endif	//TAHD_ATOM_PAIR_H
