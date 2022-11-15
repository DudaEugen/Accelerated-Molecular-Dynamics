#pragma once
#ifndef TAHD_PARALLEL_CELL_GROUP_H
#define TAHD_PARALLEL_CELL_GROUP_H

#include <vector>
#include <unordered_map>
#include "Parallel/MPI/Processes.hpp"
#include "System/CellCollection.hpp"

namespace md
{
    class ParallelCellGroup
    {
        std::vector<int> sendCounts;
        std::vector<Atom*> atoms;
        const Processes processes;
        std::size_t totalCellsCount;

        std::size_t firstSubscriberedCellIndex(std::size_t processRank) const;
        std::size_t subscriberedCellCount(std::size_t processRank) const;
    public:
        std::size_t firstSubscriberedCellIndex() const;
        std::size_t subscriberedCellCount() const;
        void exchangeAccelerations();
        void exchangeValues(std::unordered_map<Atom*, double>& values);
        void refresh(CellCollection& cells);
    };
}

#endif  // TAHD_PARALLEL_CELL_GROUP_H
