#include "AtomicSystem.h"

AtomicSystem::AtomicSystem(const substance substance, BorderConditions* borderCond)
: substance_(substance), borderConditions{ borderCond }
{
}

AtomicSystem::AtomicSystem(const std::string& substance, BorderConditions* borderCond)
: substance_(convert_to_substance(substance)), borderConditions{ borderCond }
{
}

std::vector<AtomPair>& AtomicSystem::getAtomPairs() noexcept { return atomPairs; }

std::vector<Atom>& AtomicSystem::getAtoms() noexcept { return atoms; }
