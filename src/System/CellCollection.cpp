#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include "System/CellCollection.hpp"
#include "IndexedZip.hpp"

void md::CellCollection::constructCells(
    const std::vector<md::Atom> &atoms,
    double minCellLinearSize,
    std::uint8_t extraCells)
{
    const Vector spaceSize = Position::spaceSize();
    for (
        auto [index, cellProj, spaceProj, number] :
        utils::zip::IndexedZip(cellSize, spaceSize, cellNumberInDirection))
    {
        if (spaceProj == std::numeric_limits<double>::infinity())
        {
            cellProj = minCellLinearSize;
            const auto &[min, max] = std::minmax_element(
                atoms.begin(),
                atoms.end(),
                [index](const Atom &a, const Atom &b)
                {
                    return a.getPosition().normalize()[index] < b.getPosition().normalize()[index];
                });
            double minProj = max->getPosition()[index];
            double maxProj = max->getPosition()[index];
            firstCellPosition[index] = minProj - 0.5 * cellProj - extraCells * cellProj;
            number = 2 * extraCells + 1 + static_cast<std::size_t>(std::ceil((maxProj - minProj) / cellProj));
        }
        else
        {
            firstCellPosition[index] = Position::minimalValue()[index];
            number = static_cast<std::size_t>(std::floor(spaceProj / minCellLinearSize));
            cellProj = spaceProj / number;
        }
    }

    cells.resize(
        std::accumulate(
            cellNumberInDirection.begin(),
            cellNumberInDirection.end(),
            1,
            std::multiplies<std::size_t>()
        )
    );
}

md::CellCollection::CellCollection(
    std::vector<md::Atom> &atoms,
    double minCellLinearSize,
    std::uint8_t extraCells)
{
    constructCells(atoms, minCellLinearSize, extraCells);
    refreshCells(atoms);
}

std::size_t md::CellCollection::defineContainingCellIndex(md::Position::ConstPass position) const
{
    Position normalized = position.normalize();

    std::size_t cellIndex = 0;
    std::size_t factor = 1;
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        int index = static_cast<int>(std::floor((normalized[i] - firstCellPosition[i]) / cellSize[i]));
        if (index < 0 || static_cast<std::size_t>(index) >= cellNumberInDirection[i])
        {
            throw std::runtime_error("Position outside the cells");
        }
        cellIndex += factor * index;
        factor *= cellNumberInDirection[i];
    }
    return cellIndex;
}

std::size_t md::CellCollection::getIndex(const md::Cell& cell) const
{
    return &cell - cells.data();
}

void md::CellCollection::setContainingCell(md::Atom &atom)
{
    std::size_t index = defineContainingCellIndex(atom.getPosition());
    cells[index].addAtom(atom);
}

const md::Cell& md::CellCollection::getCellByIndex(std::size_t index) const noexcept
{
    return cells[index];
}

md::Cell& md::CellCollection::getContainingCell(md::Position::ConstPass position)
{
    return cells[defineContainingCellIndex(position)];
}

md::Cell& md::CellCollection::getContainingCell(const md::Atom &atom)
{
    return getContainingCell(atom.getPosition());
}

md::Position md::CellCollection::getCellCenterPositionByIndex(std::size_t index) const
{
    md::Position position{};
    std::size_t cellsInLayers = cells.size();
    for(std::int8_t i = kDimensionalNumber - 1; i >= 0; --i)
    {
        cellsInLayers /= cellNumberInDirection[i];
        position[i] = cellSize[i] * index / cellsInLayers + cellSize[i]/2;
        index %= cellNumberInDirection[i];
    }
    return position.normalize();
}

std::vector<std::array<std::uint8_t, md::kDimensionalNumber>>
md::CellCollection::offsetIndexes(std::uint8_t dimensionalIndex) const
{
    std::vector<std::array<std::uint8_t, kDimensionalNumber>> partialOffsets;
    if (dimensionalIndex == kDimensionalNumber - 1)
    {
        partialOffsets.push_back({});
    }
    else
    {
        partialOffsets = offsetIndexes(dimensionalIndex + 1);
    }
    std::vector<std::array<std::uint8_t, kDimensionalNumber>> result;
    for (std::uint8_t i = -1; i <= 1; ++i)
    {
        for (auto partialOffset : partialOffsets)
        {
            std::array<std::uint8_t, kDimensionalNumber> offset = partialOffset;
            offset[dimensionalIndex] = i;
            result.push_back(offset);
        }
    }
    return result;
}

std::vector<md::Vector> md::CellCollection::offsets() const
{
    std::vector<Vector> result;
    for (auto &offset : offsetIndexes())
    {
        if (std::any_of(offset.begin(), offset.end(), [](std::uint8_t v){return v != 0;}))
        {
            Vector offsetVector;
            for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
            {
                offsetVector[i] = offset[i] * cellSize[i];
            }
            result.push_back(offsetVector);
        }
    }
    return result;
}

std::pair<md::Cell &, std::vector<md::Cell*>> md::CellCollection::getCellWithNeighboursByIndex(std::size_t index)
{
    return getContainingCellWithNeighbours(getCellCenterPositionByIndex(index));
}

std::pair<md::Cell &, std::vector<md::Cell*>> md::CellCollection::getContainingCellWithNeighbours(Position::ConstPass position)
{
    std::pair<md::Cell &, std::vector<Cell*>> result = {getContainingCell(position), {}};

    for (Vector::ConstPass offset : offsets())
    {
        result.second.push_back(&getContainingCell(position + offset));
    }
    return result;
}

std::pair<md::Cell &, std::vector<md::Cell*>> md::CellCollection::getContainingCellWithNeighbours(const Atom &atom)
{
    return getContainingCellWithNeighbours(atom.getPosition());
}

void md::CellCollection::refreshCells(std::vector<md::Atom> &atoms)
{
    for (auto &cell : cells)
    {
        cell.clear();
    }
    for (auto &atom : atoms)
    {
        setContainingCell(atom);
    }
}

std::size_t md::CellCollection::size() const noexcept
{
    return cells.size();
}

md::Vector md::CellCollection::getCellSize() const noexcept
{
    return cellSize;
}
