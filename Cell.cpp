#include "Cell.h"

Vector Cell::size = Vector{};

constexpr std::size_t Cell::maximumNeighborCellsNumber()
{
	int result = 1;
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result *= 3;
	}
	return result;
}

Cell::Cell(Vector::ConstVectorPass position, const size_t atomsNumber)
	: neighborCells{}, position{ position }, atoms{ atomsNumber }
{
	neighborCells.reserve(maximumNeighborCellsNumber());
}

void Cell::addNeighborCell(Cell* cell)
{
	if (neighborCells.size() < maximumNeighborCellsNumber())
	{
		neighborCells.push_back(cell);
	}
	else
	{
		throw std::length_error("Maximum number of neighbor Cells Exceeded");
	}
}

std::size_t Cell::getNeighborCellNumber() const noexcept { return neighborCells.size(); }

Cell& Cell::getNeighborCell(const size_t index) noexcept { return *(neighborCells[index]); }

Vector::ConstVectorPass Cell::getSize() noexcept { return Cell::size; }

void Cell::setSize(Vector::ConstVectorPass cellSize) noexcept { Cell::size = cellSize; }
