#pragma once
#ifndef TAHD_ATOM_NEIGHBOURSLIST_H
#define TAHD_ATOM_NEIGHBOURSLIST_H

#include <vector>
#include "Atoms/AtomPair.hpp"
#include "System/CellCollection.hpp"

namespace md
{
    class NeighboursList
    {
        CellCollection cells;
        std::vector<AtomPair> pairs;
        std::size_t subscribedCellsCount;
        std::size_t firstSubscribedCellIndex;
        double cutRadius;

        void subscribeToCells(std::size_t subscribersCount, std::size_t subscriberIndex);
    public:
        NeighboursList(
            std::vector<Atom>& atoms,
            double cutRadius,
            double minCellLinearSize,
            std::size_t subscribersCount = 1,
            std::size_t subscriberIndex = 0,
            std::uint8_t extraCells = 3
        );
        std::vector<AtomPair>& getPairs() noexcept;
        void updateDistances();
        void refresh(std::vector<Atom>& atoms);
        Vector getCellSize() const noexcept;
    };
}

#endif  // TAHD_ATOM_NEIGHBOURSLIST_H
