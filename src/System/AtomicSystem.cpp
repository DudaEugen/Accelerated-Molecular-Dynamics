#include "System/AtomicSystem.hpp"

md::AtomicSystem::AtomicSystem(const std::vector<Atom>& allAtoms, APotential* atomicPotential, 
                               BorderConditions* borderCond)
    : cells{ allAtoms, atomicPotential, borderCond }, atoms{ allAtoms }, 
      borderConditions{ borderCond }, potential{ atomicPotential }
{
}

std::vector<md::AtomPair>& md::AtomicSystem::getAtomPairs() noexcept { return atomPairs; }

std::vector<md::Atom>& md::AtomicSystem::getAtoms() noexcept { return atoms; }
