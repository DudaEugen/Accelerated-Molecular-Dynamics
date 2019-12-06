#pragma once
#ifndef TAHD_CELL_H
#define TAHD_CELL_H

#include "Atom.h"
#include <vector>

/*the whole space is divided into cubic cells whose dimensions are not less than the cutoff radius of potential. 
Then, to search for atoms that directly interact with each other, you need to use only atoms that are in the same or adjacent cells.*/
class Cell
{
private:
	/*a point is considered to be placed inside the Ñell if for i-th coordinate r[i]: 
	Cell.position[i] <= r[i] < Cell.position[i] + Cell.size[i] */
	ProjectionTuple position;
	ProjectionTuple size;				//all values must is positive
	std::vector<Cell*> neighborCells;	//this and adjacent Cells
	std::vector<Atom*> atoms;

	~Cell();
	int neighborCellsNumber();	
public:
	Cell(const ProjectionTuple position, const ProjectionTuple size);

	/*atomsNumber is the approximate number of atoms that will be contained in a cell. 
	The vector size will be set to zero, but memory will be allocated to atomsNumber of elements.
	In the future, the number of atoms can decrease and increase.*/
	Cell(const ProjectionTuple position, const ProjectionTuple size, const double atomsNumber);
	void addNeighborCell(Cell* cell);
	void addNeighborCell(Cell cell);
	void addAtom(Atom* atom);
	void addAtom(Atom atom);
	int getNeighborCellNumber() const;
	int getAtomNumber() const;
	Cell& getNeighborCell(int index) const;
	Atom& getAtom(int index) const;
	void cleanAtomList();
};

#endif	//TAHD_CELL_H
