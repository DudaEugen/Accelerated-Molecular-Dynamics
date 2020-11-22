#pragma once
#ifndef TAHD_CELL_H
#define TAHD_CELL_H

#include "AtomGroup.hpp"

/*the whole space is divided into cubic cells whose dimensions are not less than the cutoff radius of potential. 
Then, to search for atoms that directly interact with each other, you need to use only atoms that are in the same or adjacent cells.*/
class Cell
{
private:
	std::vector<Cell*> neighborCells;	//this and adjacent Cells
public:
	AtomGroup atoms;

private:
	static constexpr size_t maximumNeighborCellsNumber();

public:
	/*atomsNumber is the approximate number of atoms that will be contained in a cell. 
	The vector size will be set to zero, but memory will be allocated to atomsNumber of elements.
	In the future, the number of atoms can decrease and increase.*/
	Cell(const size_t atomsNumber = 0);
	void addNeighborCell(Cell* cell);
	std::vector<Cell*>& getNeighborCells () noexcept;
	const std::vector<Cell*>& getNeighborCells () const noexcept;
};

#endif	//TAHD_CELL_H
