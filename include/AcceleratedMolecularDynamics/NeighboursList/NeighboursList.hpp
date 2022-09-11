#pragma once
#ifndef TAHD_ATOM_NEIGHBOURSLIST_H
#define TAHD_ATOM_NEIGHBOURSLIST_H

#include <vector>
#include "Atoms/AtomPair.hpp"
#include "System/CellCollection.hpp"
#include "NeighboursList/ParallelCellGroup.hpp"

namespace md
{
    class NeighboursList
    {
        CellCollection cells;
        std::vector<AtomPair> pairs;
        ParallelCellGroup parallelCellGroup;
        double cutRadius;

    public:
        NeighboursList(
            std::vector<Atom>& atoms,
            double cutRadius,
            double minCellLinearSize,
            std::uint8_t extraCells = 3
        );
        std::vector<AtomPair>& getPairs() noexcept;
        void updateDistances();
        void refresh(std::vector<Atom>& atoms);
        Vector getCellSize() const noexcept;
        ParallelCellGroup& getParallelCellGroups() noexcept;
    };
}

#endif  // TAHD_ATOM_NEIGHBOURSLIST_H
