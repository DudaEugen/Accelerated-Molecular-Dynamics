#include "Cell.h"

constexpr std::size_t Cell::maximumNeighborCellsNumber()
{
	int result = 1;
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result *= 3;
	}
	return result;
}

Cell::Cell(const size_t atomsNumber)
	: neighborCells{}, atoms{ atomsNumber }
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

std::vector<Cell*>& Cell::getNeighborCells () noexcept 
{ 
	return neighborCells; 
}

const std::vector<Cell*>& Cell::getNeighborCells () const noexcept 
{ 
	return neighborCells; 
}
