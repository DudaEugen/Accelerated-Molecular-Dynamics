#pragma once
#ifndef TAHD_SYSTEM_H
#define TAHD_SYSTEM_H

#include "AtomPair.h"
#include "Cell.h"
#include "Substances.h"

class System
{
	std::vector<Atom> atoms;
	std::vector<Cell> cells;
	std::vector<AtomPair> atomPairs;
	substance substance_;
public:
	System(const substance substance);
	System(const std::string& substance);
	static void setBorderConditions(BorderConditions* borderCond);
	std::vector<AtomPair>& getAtomPairs();
	std::vector<Atom>& getAtoms();
};

#endif	//TAHD_SYSTEM_H
