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
        std::array<std::size_t, kDimensionalNumber> cellNumberInDirection;
        Position firstCellPosition;
        Vector cellSize;

        std::vector<Vector> offsets(std::uint8_t index = 0) const;
        void constructCells(
            const std::vector<md::Atom>& atoms,
            const APotential* const potential,
            std::uint8_t extraCells
        );
        std::size_t defineContainingCellIndex(Position::ConstPass position) const;
        void setContainingCell(Atom& atom);
    public:
        CellCollection(
            std::vector<Atom>& atoms,
            const APotential* const potential,
            std::uint8_t extraCells = 3
        );
        CellCollection(
            std::vector<Atom>& atoms,
            const std::vector<APotential*>& potential,
            std::uint8_t extraCells = 3
        );
        const Cell& getContainingCell(Position::ConstPass position) const;
        const Cell& getContainingCell(const Atom& atom) const;
        const std::vector<std::reference_wrapper<const Cell>> getContainingCellWithNeighbours(
            Position::ConstPass position
        ) const;
        const std::vector<std::reference_wrapper<const Cell>> getContainingCellWithNeighbours(
            const Atom& atom
        ) const;
        void refreshCells(std::vector<Atom>& atoms);
    };
}

#endif  //TAHD_CELL_COLLECTION_H
