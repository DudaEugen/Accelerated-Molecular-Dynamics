#include "AtomicSystem.hpp"

AtomicSystem::AtomicSystem(const std::vector<Atom>& allAtoms, APotential* atomicPotential, BorderConditions* borderCond)
: cells{ allAtoms, atomicPotential, borderCond }, atoms{ allAtoms }, borderConditions{ borderCond }, potential{ atomicPotential }
{
}

std::vector<AtomPair>& AtomicSystem::getAtomPairs() noexcept { return atomPairs; }

std::vector<Atom>& AtomicSystem::getAtoms() noexcept { return atoms; }
