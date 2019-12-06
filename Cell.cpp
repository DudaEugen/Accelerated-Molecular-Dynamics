#include "Cell.h"

Cell::~Cell()
{
	std::vector<Atom*>().swap(atoms);
	std::vector<Cell*>().swap(neighborCells);
}

int Cell::neighborCellsNumber()
{
	return pow(3, DIMENSIONAL_NUMBER);
}

Cell::Cell(const ProjectionTuple position, const ProjectionTuple size) 
	: position{ position }, size{ size }, neighborCells{}, atoms{}
{
	neighborCells.reserve(neighborCellsNumber());
}

Cell::Cell(const ProjectionTuple position, const ProjectionTuple size, const double atomsNumber) 
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

void Cell::addNeighborCell(Cell cell) {	addNeighborCell(&cell); }

void Cell::addAtom(Atom* atom) { atoms.push_back(atom); }

void Cell::addAtom(Atom atom) {	addAtom(&atom); }

int Cell::getNeighborCellNumber() const { return neighborCells.size(); }

int Cell::getAtomNumber() const { return atoms.size(); }

Cell& Cell::getNeighborCell(int index) const { return *neighborCells[index]; }

Atom& Cell::getAtom(int index) const { return *atoms[index]; }

void Cell::cleanAtomList() { atoms.resize(0); }
