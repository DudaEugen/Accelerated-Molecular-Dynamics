#include <exception>
#include "NeighboursList/NeighboursList.hpp"
#include "IndexedZip.hpp"

md::NeighboursList::NeighboursList(
    std::vector<md::Atom>& atoms,
    double cutRadius,
    double minCellLinearSize,
    std::uint8_t extraCells
)
    : cells{ atoms, minCellLinearSize, extraCells }, cutRadius{cutRadius}, parallelCellGroup{}
{
    if (cutRadius > minCellLinearSize) {
        throw std::runtime_error("Cut radius can't be bigger than minimum cell size");
    }
    if (cutRadius < 0 || minCellLinearSize < 0) {
        throw std::runtime_error("Cut radius and minimum cell size can't be negative");
    }
    refresh(atoms);
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
    cells.refreshCells(atoms);
    parallelCellGroup.refresh(cells);

    pairs.clear();
    auto updatePairs = [this](Atom& first, Atom& second)
    {
        pairs.emplace_back(first, second);
        if (pairs.back().getDistance() > cutRadius)
        {
            pairs.pop_back();
        }
    };

    std::size_t firstSubscribedCellIndex = parallelCellGroup.firstSubscriberedCellIndex();
    std::size_t subscribedCellsCount = parallelCellGroup.subscriberedCellCount();
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
