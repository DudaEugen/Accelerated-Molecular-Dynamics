#pragma once
#ifndef TAHD_ATOMIC_SYSTEM_H
#define TAHD_ATOMIC_SYSTEM_H

#include "Atoms/AtomPair.hpp"
#include "Potential/APotential.hpp"

namespace md
{
	class AtomicSystem
	{
		std::vector<Atom> atoms;
		std::vector<AtomPair> atomPairs;
		APotential* potential;

	public:
		AtomicSystem(const std::vector<Atom>& allAtoms, APotential* atomicPotential);
		std::vector<AtomPair>& getAtomPairs() noexcept;
		std::vector<Atom>& getAtoms() noexcept;
	};
}

#endif	//TAHD_ATOMIC_SYSTEM_H
