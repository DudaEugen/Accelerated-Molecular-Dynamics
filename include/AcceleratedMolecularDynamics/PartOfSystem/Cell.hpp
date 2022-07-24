#pragma once
#ifndef TAHD_CELL_H
#define TAHD_CELL_H

#include <vector>
#include "Atoms/Atom.hpp"
#include "Vector/Position.hpp"

namespace md
{
	class Cell
	{
		std::vector<Atom*> atoms;
	public:
		std::vector<Atom*>& getAtoms() noexcept;
		void addAtom(Atom& atom);
		void clear() noexcept;
	};
}

#endif	//TAHD_CELL_H
