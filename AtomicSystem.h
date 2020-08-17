#pragma once
#ifndef TAHD_ATOMIC_SYSTEM_H
#define TAHD_ATOMIC_SYSTEM_H

#include "AtomPair.h"
#include "Cell.h"
#include "Substances.h"

class AtomicSystem
{
	std::vector<Atom> atoms;
	std::vector<Cell> cells;
	std::vector<AtomPair> atomPairs;
	BorderConditions* borderConditions;
	substance substance_;
public:
	AtomicSystem(const substance substance, BorderConditions* borderConditions = nullptr);
	AtomicSystem(const std::string& substance, BorderConditions* borderConditions = nullptr);
	std::vector<AtomPair>& getAtomPairs() noexcept;
	std::vector<Atom>& getAtoms() noexcept;
};

#endif	//TAHD_ATOMIC_SYSTEM_H
