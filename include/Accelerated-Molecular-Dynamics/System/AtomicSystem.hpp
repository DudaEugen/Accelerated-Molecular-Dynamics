#pragma once
#ifndef TAHD_ATOMIC_SYSTEM_H
#define TAHD_ATOMIC_SYSTEM_H

#include "Atoms/AtomPair.hpp"
#include "CellCollection.hpp"

namespace md
{
	class AtomicSystem
	{
		CellCollection cells;
		std::vector<Atom> atoms;
		std::vector<AtomPair> atomPairs;
		BorderConditions* borderConditions;
		APotential* potential;

	public:
		// Borders are surfeces, that have i-th coordionate x[i] such that x[i] == 0 or x[i] == size[i], if borderConditions[i] is periodic
		AtomicSystem(const std::vector<Atom>& allAtoms, APotential* atomicPotential, BorderConditions* borderConditions = nullptr);
		std::vector<AtomPair>& getAtomPairs() noexcept;
		std::vector<Atom>& getAtoms() noexcept;
	};
}

#endif	//TAHD_ATOMIC_SYSTEM_H
