#pragma once
#ifndef TAHD_ATOM_GROUP_H
#define TAHD_ATOM_GROUP_H

#include "Atoms/Atom.hpp"
#include <vector>

namespace md
{
	/*This class is wrapped for dynamic array of pointers to atoms*/
	class AtomGroup
	{
	private:
		std::vector<Atom*> atoms;
	public:
		AtomGroup(const size_t reservedNumber = 0);
		void reserve(const size_t number);
		void addAtom(Atom* atom);
		size_t getAtomNumber() const noexcept;
		void clearList() noexcept;
		Atom& operator [] (const size_t index);
		Atom* remove(const size_t index);
	};
}

#endif	//TAHD_ATOM_GROUP_H
