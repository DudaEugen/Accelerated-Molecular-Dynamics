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
	substance substance_;
public:
	AtomicSystem(const substance substance);
	AtomicSystem(const std::string& substance);
	static void setBorderConditions(BorderConditions* borderCond);
	std::vector<AtomPair>& getAtomPairs();
	std::vector<Atom>& getAtoms();
};

#endif	//TAHD_ATOMIC_SYSTEM_H
