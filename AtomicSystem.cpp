#include "AtomicSystem.h"

AtomicSystem::AtomicSystem(const substance substance)
: substance_(substance)
{
}

AtomicSystem::AtomicSystem(const std::string& substance)
: substance_(convert_to_substance(substance))
{
}

void AtomicSystem::setBorderConditions(BorderConditions* borderCond)
{
	AtomPair::setBorderConditions(borderCond);
}

std::vector<AtomPair>& AtomicSystem::getAtomPairs() { return atomPairs; }

std::vector<Atom>& AtomicSystem::getAtoms() { return atoms; }
