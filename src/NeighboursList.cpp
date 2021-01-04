#include "NeighboursList.hpp"

md::NeighboursList::Neighbour::Neighbour(AtomPair* const aPair, const AtomPair::index indexOfNeighbour) noexcept
    : pair{ aPair }, neighbourIndex{ indexOfNeighbour }
{
}

md::Atom& md::NeighboursList::Neighbour::getNeighbourAtom() const noexcept
{
    return pair->getAtomByIndex(neighbourIndex);
}

md::AtomPair& md::NeighboursList::Neighbour::getPair() const noexcept
{
    return *pair;
}

md::NeighboursList::NeighboursList(Atom& first, Atom& last)
    : neighborsTable{}, firstAtom{ &first }
{
    std::size_t size = &last - &first + 1;
    neighborsTable.reserve(size);
    for (std::size_t i = 0; i < size; ++i)
        neighborsTable.push_back(std::vector<Neighbour>{});
}

md::NeighboursList::NeighboursList(Atom& first, const std::size_t atomNumber)
    : NeighboursList{ first, *(&first + atomNumber) }
{
}

void md::NeighboursList::tryAddPairToAtomLine(AtomPair& pair, const AtomPair::index index)
{
    Atom* atom = &(pair.getAtomByIndex(index));
    if (atom >= firstAtom && atom < firstAtom + neighborsTable.size())
    {
        using apIndex = AtomPair::index;
        apIndex indexOfNeighbour = index == apIndex::first ? apIndex::second : apIndex::first;
        neighborsTable[atom - firstAtom].push_back(Neighbour(&pair, indexOfNeighbour));
    }
}

void md::NeighboursList::addPair(AtomPair& pair)
{
    tryAddPairToAtomLine(pair, AtomPair::index::first);
    tryAddPairToAtomLine(pair, AtomPair::index::second);
}

std::vector<md::NeighboursList::Neighbour>& md::NeighboursList::getNeighboursOfAtom(const Atom& atom)
{
    return neighborsTable[&atom - firstAtom];
}
