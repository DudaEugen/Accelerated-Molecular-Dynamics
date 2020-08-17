#pragma once
#ifndef TAHD_ATOMIC_SYSTEM_H
#define TAHD_ATOMIC_SYSTEM_H

#include <algorithm>
#include "AtomPair.h"
#include "Cell.h"
#include "Potential/APotential.h"

class AtomicSystem
{
	std::vector<Atom> atoms;
	std::vector<Cell> cells;
	std::vector<AtomPair> atomPairs;
	Vector firstCellPosition;
	Vector cellSize;
	std::size_t cellNumberInDirection[DIMENSIONAL_NUMBER];
	BorderConditions* borderConditions;
	APotential* potential;

	void computeCellSize();
public:
	// Borders are surfeces, that have i-th coordionate x[i] such that x[i] == 0 or x[i] == size[i], if borderConditions[i] is periodic
	AtomicSystem(const std::vector<Atom>& allAtoms, APotential* atomicPotential, BorderConditions* borderConditions = nullptr);
	std::vector<AtomPair>& getAtomPairs() noexcept;
	std::vector<Atom>& getAtoms() noexcept;
};

#endif	//TAHD_ATOMIC_SYSTEM_H
