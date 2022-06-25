#pragma once
#ifndef TAHD_ATOM_PAIR_H
#define TAHD_ATOM_PAIR_H

#include <utility>
#include "Atom.hpp"

namespace md
{
	/*AtomPair class is replying for computing and storing: 
	distances between Atoms and differences of Atoms coordinates */
	class AtomPair
	{
	private: 
		Vector dProjections;
		double distance;
		Atom& firstAtom;
		Atom& secondAtom;

	public:
		AtomPair(Atom& first, Atom& second) noexcept;
		Atom& getFirst() const noexcept;
		Atom& getSecond() const noexcept;
		double getDistance() const noexcept;
		/* position of the second atom relative to the first.
		Get difference between coordinats of atoms: second - first, which was obtained during the 
		last call to the computeDistance or constructor */
		Vector getProjections() const noexcept;
		std::pair<double, Vector> getDistanceWithProjections() const noexcept;
		std::pair<double, Vector> computeDistanceWithProjections();
	};
}

#endif	//TAHD_ATOM_PAIR_H
