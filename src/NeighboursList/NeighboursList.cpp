#include <cmath>
#include <exception>
#include "NeighboursList/NeighboursList.hpp"
#include "IndexedZip.hpp"

md::NeighboursList::NeighboursList(
    std::vector<md::Atom>& atoms,
    double cutRadius,
    double minCellLinearSize,
    std::size_t subscribersCount,
    std::size_t subscriberIndex,
    std::uint8_t extraCells
)
    : cells{ atoms, minCellLinearSize, extraCells }, cutRadius{cutRadius}
{
    if (cutRadius > minCellLinearSize) {
        throw std::runtime_error("Cut radius can't be bigger than minimum cell size");
    }
    if (cutRadius < 0 || minCellLinearSize < 0) {
        throw std::runtime_error("Cut radius and minimum cell size can't be negative");
    }
    subscribeToCells(subscribersCount, subscriberIndex);
    refresh(atoms);
}

void md::NeighboursList::subscribeToCells(std::size_t subscribersCount, std::size_t subscriberIndex)
{
    std::size_t cellsCount = static_cast<std::size_t>(std::floor(cells.size() / subscribersCount));
    firstSubscribedCellIndex = subscriberIndex * cellsCount;
    if (subscriberIndex != (subscribersCount-1))
    {
        subscribedCellsCount = cellsCount;
    }
    else
    {
        subscribedCellsCount = cells.size() - firstSubscribedCellIndex;
    }
}

std::vector<md::AtomPair>& md::NeighboursList::getPairs() noexcept
{
    return pairs;
}

void md::NeighboursList::updateDistances()
{
    for (auto& pair: pairs)
    {
        pair.computeDistanceWithProjections();
    }
}

void md::NeighboursList::refresh(std::vector<md::Atom>& atoms)
{
    pairs.clear();
    cells.refreshCells(atoms);
    auto updatePairs = [this](Atom& first, Atom& second)
    {
        pairs.emplace_back(first, second);
        if (pairs.back().getDistance() > cutRadius)
        {
            pairs.pop_back();
        }
    };

    for (
        std::size_t cellIndex = firstSubscribedCellIndex;
        cellIndex < firstSubscribedCellIndex + subscribedCellsCount;
        ++cellIndex
    )
    {
        auto [cell, neighbours] = cells.getCellWithNeighboursByIndex(cellIndex);
        auto& atoms = cell.getAtoms();
        for (auto [index, atom]: utils::zip::IndexedZip(atoms))
        {
            for (std::size_t i = index + 1; i < atoms.size(); ++i)
            {
                updatePairs(*atom, *(atoms[i]));
            }

            for (auto neighbour: neighbours)
            {
                if (cells.getIndex(*neighbour) > cellIndex)
                {
                    for (auto at: neighbour->getAtoms())
                    {
                        updatePairs(*atom, *at);
                    }
                }
            }
        }
    }
}

md::Vector md::NeighboursList::getCellSize() const noexcept
{
    return cells.getCellSize();
}
