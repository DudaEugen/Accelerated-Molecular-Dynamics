#pragma once
#ifndef TAHD_ATOM_PAIR_H
#define TAHD_ATOM_PAIR_H

#include "Atom.hpp"
#include "BorderConditions.hpp"

namespace md
{
	/*AtomPair class is replying for computing and storing: an distances between Atoms and differences of Atoms coordinates;
	it is known Atom Pair: atoms contain in same stream or in different*/
	class AtomPair
	{
	private:
		Vector dProjections;
		Atom* atomPair[2];
		double distance;
		bool isAtomsFromSameStream;

	public:
		enum class index {
			first = 0,
			second = 1,
		};

		AtomPair(Atom& first, Atom& second) noexcept;
		AtomPair(Atom& first, Atom& second, const double d, const Vector deltaCoordinates) noexcept;
		Atom& getAtomByIndex(const index i) const noexcept;
		Atom& getAtomWithAnotherIndex(const index i) const noexcept;
		Atom& getFirst() const noexcept;
		Atom& getSecond() const noexcept;
		double getDistance() const noexcept;
		Vector::ConstPass getDistanceProjections() const noexcept;	/* position of the second atom relative to the first.
				Get difference between coordinats of atoms: second - first, which was obtained during the 
				last call to the computeDistance or constructor */ 
		bool getIsAtomsFromSameStream() const noexcept;
		void setIsAtomsFromSameStream(const bool isSame) noexcept;
		double computeDistance() noexcept;
		double computeDistance(const BorderConditions& borderConditions) noexcept;
	};
}

#endif	//TAHD_ATOM_PAIR_H
