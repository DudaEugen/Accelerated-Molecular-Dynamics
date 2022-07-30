#pragma once
#ifndef TAHD_ATOMIC_SYSTEM_H
#define TAHD_ATOMIC_SYSTEM_H

#include "Atoms/AtomPair.hpp"
#include "Potential/IPotential.hpp"

namespace md
{
	class AtomicSystem
	{
		std::vector<Atom> atoms;
		std::vector<AtomPair> atomPairs;
		IPotential* potential;

	public:
		AtomicSystem(const std::vector<Atom>& allAtoms, IPotential* atomicPotential);
		std::vector<AtomPair>& getAtomPairs() noexcept;
		std::vector<Atom>& getAtoms() noexcept;
	};
}

#endif	//TAHD_ATOMIC_SYSTEM_H
