#include "Cell.h"


size_t Cell::neighborCellsNumber()
{
	return pow(3, DIMENSIONAL_NUMBER);
}

Cell::Cell(const Vector& position, const Vector& size, const size_t atomsNumber) 
	: position{ position }, size{ size }, neighborCells{}, atoms{ atomsNumber }
{
	neighborCells.reserve(neighborCellsNumber());
}

void Cell::addNeighborCell(Cell* cell)
{
	if (neighborCells.size() < neighborCellsNumber())
	{
		neighborCells.push_back(cell);
	}
	else
	{
		throw std::length_error("Maximum number of neighbor Cells Exceeded");
	}
}

std::size_t Cell::getNeighborCellNumber() const { return neighborCells.size(); }

Cell& Cell::getNeighborCell(const size_t index) { return *neighborCells[index]; }
