#include "PartOfSystem/Cell.hpp"

constexpr std::size_t md::Cell::maximumNeighborCellsNumber()
{
	int result = 1;
	for (Vector::projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		result *= 3;
	}
	return result;
}

md::Cell::Cell(const size_t atomsNumber)
	: neighborCells{}, atoms{ atomsNumber }
{
	neighborCells.reserve(maximumNeighborCellsNumber());
}

void md::Cell::addNeighborCell(Cell* cell)
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

std::vector<md::Cell*>& md::Cell::getNeighborCells () noexcept 
{ 
	return neighborCells; 
}

const std::vector<md::Cell*>& md::Cell::getNeighborCells () const noexcept 
{ 
	return neighborCells; 
}
