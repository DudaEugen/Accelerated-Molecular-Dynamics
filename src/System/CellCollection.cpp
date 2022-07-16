#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include "System/CellCollection.hpp"
#include "IndexedZip.hpp"

void md::CellCollection::constructCells(
    const std::vector<md::Atom>& atoms,
    const md::APotential* const potential,
    std::uint8_t extraCells
)
{
    double minSize = potential->getCutRadius();

    const Vector spaceSize = Position::spaceSize();
    for (
        auto [index, cellProj, spaceProj, number]:
        utils::zip::IndexedZip(cellSize, spaceSize, cellNumberInDirection)
    )
    {
        if (spaceProj == std::numeric_limits<double>::infinity())
        {
            cellProj = minSize;
            const auto& [min, max] = std::minmax_element(
                atoms.begin(),
                atoms.end(),
                [index](const Atom& a, const Atom& b)
                {
                    return a.getPosition().normalize()[index] < b.getPosition().normalize()[index];
                }
            );
            double minProj = max->getPosition()[index];
            double maxProj = max->getPosition()[index];
            firstCellPosition[index] = minProj - 0.5 * cellProj - extraCells * cellProj;
            number = 2 * extraCells + 1 + static_cast<std::size_t>(std::ceil((maxProj - minProj) / cellProj));
        }
        else
        {
            firstCellPosition[index] = Position::minimalValue()[index];
            number = static_cast<std::size_t>(std::floor(spaceProj / minSize));
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
    std::vector<md::Atom>& atoms,
    const md::APotential* const potential,
    std::uint8_t extraCells
)
{
    constructCells(atoms, potential, extraCells);
    refreshCells(atoms);
}

md::CellCollection::CellCollection(
    std::vector<md::Atom>& atoms,
    const std::vector<md::APotential*>& potential,
    std::uint8_t extraCells
)
    : CellCollection{
        atoms,
        *std::max_element(
            potential.begin(),
            potential.end(),
            [](const APotential* a, const APotential* b){ return a->getCutRadius() < b->getCutRadius(); }
        ),
        extraCells
    }
{
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

void md::CellCollection::setContainingCell(md::Atom& atom)
{
    std::size_t index = defineContainingCellIndex(atom.getPosition());
    cells[index].addAtom(atom);
}

const md::Cell& md::CellCollection::getContainingCell(md::Position::ConstPass position) const
{
    return cells[defineContainingCellIndex(position)];
}

const md::Cell& md::CellCollection::getContainingCell(const md::Atom& atom) const
{
    return getContainingCell(atom.getPosition());
}

std::vector<md::Vector> md::CellCollection::offsets(std::uint8_t index) const
{
    std::vector<Vector> partialOffsets;
    if (index == kDimensionalNumber - 1)
    {
        partialOffsets.push_back(Vector{});
    }
    else
    {
        partialOffsets = offsets(index + 1);
    }
    std::vector<Vector> result;
    for (std::uint8_t i = -1; i <= 1; ++i)
    {
        for (Vector::ConstPass partialOffset: partialOffsets)
        {
            Vector offset = partialOffset;
            offset[index] = i * cellSize[index];
            result.push_back(offset);
        }
    }
    return result;
}

const std::vector<std::reference_wrapper<const md::Cell>>
md::CellCollection::getContainingCellWithNeighbours(Position::ConstPass position) const
{
    std::vector<std::reference_wrapper<const md::Cell>> result;
    for (Vector::ConstPass offset: offsets())
    {
        result.push_back(getContainingCell(position + offset));
    }
    return result;
}

const std::vector<std::reference_wrapper<const md::Cell>> 
md::CellCollection::getContainingCellWithNeighbours(const Atom& atom) const
{
    return getContainingCellWithNeighbours(atom.getPosition());
}

void md::CellCollection::refreshCells(std::vector<md::Atom>& atoms)
{
    for(auto& cell: cells)
    {
        cell.clear();
    }
    for(auto& atom: atoms)
    {
        setContainingCell(atom);
    }
}
