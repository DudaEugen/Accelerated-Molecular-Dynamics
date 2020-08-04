#pragma once
#ifndef TAHD_NEIGHBOURS_LIST_H
#define TAHD_NEIGHBOURS_LIST_H

#include <vector>
#include "AtomPair.h"

/* All atoms whose neighbors are tracked must be sequentially located in a linear section of memory 
from firstAtom by lastAtom. Atom-neighbours can be located any where */
class NeighboursList
{
public:
    class Neighbour;

private:
    std::vector< std::vector<Neighbour>> neighborsTable;
    Atom* const firstAtom;

public:
    class Neighbour
    {
        AtomPair* const pair;
        const AtomPair::index neighbourIndex;

        friend class NeighboursList;
        Neighbour(AtomPair* const aPair, const AtomPair::index index) noexcept;
    public:
        Atom& getNeighbourAtom() const noexcept;
        AtomPair& getPair() const noexcept;
    };

    NeighboursList(Atom& first, Atom& last);
    NeighboursList(Atom& first, const std::size_t atomNumber);
private:
    void tryAddPairToAtomLine(AtomPair& pair, const AtomPair::index index);
public:
    void addPair(AtomPair& pair);
    std::vector<Neighbour>& getNeighboursofAtom(const Atom& atom);
};

#endif  //TAHD_NEIGHBOURS_LIST_H
