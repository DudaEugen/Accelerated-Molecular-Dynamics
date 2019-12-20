#include "Cell.h"


int Cell::neighborCellsNumber()
{
	int result = 1;
	for (unsigned short int i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result *= i;
	}
	return result;
}

Cell::Cell(const ProjectionTuple& position, const ProjectionTuple& size, const size_t atomsNumber) 
	: position{ position }, size{ size }, neighborCells{}, atoms{}
{
	neighborCells.reserve(neighborCellsNumber());
	atoms.reserve(atomsNumber);
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

void Cell::addAtom(Atom* atom) { atoms.push_back(atom); }

std::size_t Cell::getNeighborCellNumber() const { return neighborCells.size(); }

std::size_t Cell::getAtomNumber() const { return atoms.size(); }

Cell& Cell::getNeighborCell(const size_t index) { return *neighborCells[index]; }

Atom& Cell::getAtom(const size_t index) { return *atoms[index]; }

void Cell::cleanAtomList() { atoms.resize(0); }
