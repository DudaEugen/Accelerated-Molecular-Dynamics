#include "NeighboursList.h"

NeighboursList::Neighbour::Neighbour(AtomPair* const aPair, const AtomPair::index index) noexcept
    : pair{ aPair }, neighbourIndex{ index }
{
}

Atom& NeighboursList::Neighbour::getNeighbourAtom() const noexcept
{
    return pair->getAtomByIndex(neighbourIndex);
}

AtomPair& NeighboursList::Neighbour::getPair() const noexcept
{
    return *pair;
}

NeighboursList::NeighboursList(Atom& first, Atom& last)
    : neighborsTable{}, firstAtom{ &first }
{
    std::size_t size = &last - &first + 1;
    neighborsTable.reserve(size);
    for (std::size_t i = 0; i < size; ++i)
        neighborsTable.push_back(std::vector<Neighbour>{});
}

NeighboursList::NeighboursList(Atom& first, const std::size_t atomNumber)
    : NeighboursList{ first, *(&first + atomNumber) }
{
}

void NeighboursList::tryAddPairToAtomLine(AtomPair& pair, const AtomPair::index index)
{
    Atom* atom = &(pair.getAtomByIndex(index));
    if (atom >= firstAtom && atom < firstAtom + neighborsTable.size())
        neighborsTable[atom - firstAtom].push_back(Neighbour(&pair, index));
}

void NeighboursList::addPair(AtomPair& pair)
{
    tryAddPairToAtomLine(pair, AtomPair::index::first);
    tryAddPairToAtomLine(pair, AtomPair::index::second);
}

std::vector<NeighboursList::Neighbour>& NeighboursList::getNeighboursofAtom(const Atom& atom)
{
    return neighborsTable[&atom - firstAtom];
}
