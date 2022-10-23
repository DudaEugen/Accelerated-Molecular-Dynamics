#include <cmath>
#include "NeighboursList/ParallelCellGroup.hpp"

std::size_t md::ParallelCellGroup::firstSubscriberedCellIndex(std::size_t processRank) const
{
    std::size_t cellsCountPerGroup = static_cast<std::size_t>(std::floor(totalCellsCount / processes.getCount()));
    return processRank * cellsCountPerGroup;
}

std::size_t md::ParallelCellGroup::subscriberedCellCount(std::size_t processRank) const
{
    if (processRank != (processes.getCount()-1))
        return firstSubscriberedCellIndex(processRank + 1) - firstSubscriberedCellIndex(processRank);
    return totalCellsCount - firstSubscriberedCellIndex(processRank);
}

std::size_t md::ParallelCellGroup::firstSubscriberedCellIndex() const
{
    return firstSubscriberedCellIndex(processes.getRank());
}

std::size_t md::ParallelCellGroup::subscriberedCellCount() const
{
    return subscriberedCellCount(processes.getRank());
}

void md::ParallelCellGroup::exchangeAccelerations()
{
    if (!sendCounts.size() || !atoms.size() || !totalCellsCount)
        throw std::runtime_error("ParallelCellGroup isn't refreshed");
    processes.exchangeAccelerations(atoms, sendCounts);
}

void md::ParallelCellGroup::refresh(CellCollection& cells)
{
    sendCounts.resize(0);
    atoms.resize(0);
    totalCellsCount = cells.size();
    for (unsigned processRank = 0; processRank < processes.getCount(); ++processRank)
    {
        sendCounts.push_back(0);
        std::size_t firstCellIndex = firstSubscriberedCellIndex(processRank);
        std::size_t cellsCount = subscriberedCellCount(processRank);
        for (std::size_t cellIndex = firstCellIndex; cellIndex < firstCellIndex + cellsCount; ++cellIndex)
        {
            Cell& cell = cells.getCellByIndex(cellIndex);
            for (auto atom: cell.getAtoms())
            {
                atoms.push_back(atom);
            }
            sendCounts[processRank] += cell.getAtoms().size();
        }
    }
}
