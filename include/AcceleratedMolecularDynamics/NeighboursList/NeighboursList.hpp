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
        std::size_t subscribedCellsCount;
        std::size_t firstSubscribedCellIndex;
        std::vector<AtomPair> pairs;

        void subscribeToCells(std::size_t subscribersCount, std::size_t subscriberIndex);
    public:
        NeighboursList(
            std::vector<Atom>& atoms,
            const APotential* const potential,
            std::size_t subscribersCount = 1,
            std::size_t subscriberIndex = 0,
            std::uint8_t extraCells = 3
        );
        NeighboursList(
            std::vector<Atom>& atoms,
            const std::vector<APotential*>& potential,
            std::size_t subscribersCount = 1,
            std::size_t subscriberIndex = 0,
            std::uint8_t extraCells = 3
        );
        std::vector<AtomPair>& getPairs() noexcept;
        void updateDistances();
        void refresh(std::vector<Atom>& atoms);
    };
}

#endif  // TAHD_ATOM_NEIGHBOURSLIST_H
