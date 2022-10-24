#pragma once
#ifndef TAHD_CELL_COLLECTION_H
#define TAHD_CELL_COLLECTION_H

#include "PartOfSystem/Cell.hpp"

namespace md
{
    class CellCollection
    {
        std::vector<Cell> cells;
        std::array<std::size_t, kDimensionalNumber> cellNumberInDirection;
        Position firstCellPosition;
        Vector cellSize;

        std::vector<std::array<std::uint8_t, kDimensionalNumber>>
        offsetIndexes(std::uint8_t dimensionalIndex = 0) const;

        std::vector<Vector> offsets() const;
        void constructCells(
            const std::vector<md::Atom>& atoms,
            double minCellLinearSize,
            std::uint8_t extraCells
        );
        void setContainingCell(Atom& atom);
        md::Position getCellCenterPositionByIndex(std::size_t index) const;
    public:
        CellCollection(
            std::vector<Atom>& atoms,
            double minCellLinearSize,
            std::uint8_t extraCells = 2
        );
        std::size_t defineContainingCellIndex(Position::ConstPass position) const;
        std::size_t getIndex(const Cell& cell) const;
        Cell& getCellByIndex(std::size_t index) noexcept;
        Cell& getContainingCell(Position::ConstPass position);
        Cell& getContainingCell(const Atom& atom);

        std::pair<Cell&, std::vector<Cell*>> getCellWithNeighboursByIndex(std::size_t index);
        std::pair<Cell&, std::vector<Cell*>> getContainingCellWithNeighbours(Position::ConstPass position);
        std::pair<Cell&, std::vector<Cell*>> getContainingCellWithNeighbours(const Atom& atom);

        void refreshCells(std::vector<Atom>& atoms);
        std::size_t size() const noexcept;
        Vector getCellSize() const noexcept;
    };
}

#endif  //TAHD_CELL_COLLECTION_H
