#pragma once
#ifndef TAHD_CELL_COLLECTION_H
#define TAHD_CELL_COLLECTION_H

#include "PartOfSystem/Cell.hpp"
#include "Potential/APotential.hpp"

namespace md
{
    class CellCollection
    {
        std::vector<Cell> cells;
        Vector firstCellPosition;
        Vector cellSize;
        std::array<std::size_t, kDimensionalNumber> cellNumberInDirection;
        BorderConditions* borderConditions;

        // getOffsetFactorInDirection()[i] element is value that need add for offset by 1 cell to i-th direction
        std::array<std::size_t, kDimensionalNumber> getOffsetFactorInDirection() const noexcept;
        // getOffsetBySizeInDirection()[i] element is value that need add for offset by size of cellCollection to i-th direction
        std::array<std::size_t, kDimensionalNumber> getOffsetBySizeInDirection() const noexcept;
        std::array<std::size_t, kDimensionalNumber> getOffsetBySizeInDirection(PassConstArrayT<std::size_t> 
                                                                            offsetFactorInDirection) const noexcept;
        // compute and set cellSize, firstCellPosition, return number of cell
        std::size_t computeAndSetParameters(const std::vector<Atom>& atoms, const APotential* potential);
        void createCells(const std::size_t cellsNumber);                // create empty cells
        void computeAndSetNeighbours();                                 // for each cell set adjacent cells including self
    public:
        CellCollection(const std::vector<Atom>& atoms, const APotential* potential, BorderConditions* borderCond = nullptr);
        std::vector<Cell>& getCells() noexcept;
        const std::vector<Cell>& getCells() const noexcept;
        Cell& findCellContainingVector(Vector::ConstPass vector);
        Cell& findCellContainingAtom(const Atom& atom);
    };
}

#endif  //TAHD_CELL_COLLECTION_H
