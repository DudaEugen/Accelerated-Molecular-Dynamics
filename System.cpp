#include "System.h"

System::System(const substance substance)
: substance_(substance)
{
}

System::System(const std::string& substance)
: substance_(convert_to_substance(substance))
{
}

void System::setBorderConditions(BorderConditions* borderCond)
{
	AtomPair::setBorderConditions(borderCond);
}

std::vector<AtomPair>& System::getAtomPairs() { return atomPairs; }

std::vector<Atom>& System::getAtoms() { return atoms; }
