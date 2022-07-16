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
		std::vector<std::reference_wrapper<Atom>> atoms;
	public:
		const std::vector<std::reference_wrapper<Atom>>& getAtoms() const noexcept;
		void addAtom(Atom& atom);
		void clear() noexcept;
	};
}

#endif	//TAHD_CELL_H
