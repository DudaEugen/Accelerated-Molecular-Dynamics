#include "Part of System/AtomGroup.hpp"

md::AtomGroup::AtomGroup(const size_t reservedNumber) : atoms{}
{
	atoms.reserve(reservedNumber);
}

void md::AtomGroup::reserve(const size_t number)
{
	atoms.reserve(number);
}

void md::AtomGroup::addAtom(Atom* atom)
{
	atoms.push_back(atom);
}

size_t md::AtomGroup::getAtomNumber() const noexcept { return atoms.size(); }

void md::AtomGroup::clearList() noexcept { atoms.resize(0); }

md::Atom& md::AtomGroup::operator [] (const size_t index)
{
	return *atoms[index];
}

md::Atom* md::AtomGroup::remove(const size_t index)
{
	Atom* ptr = atoms[index];
	atoms.erase(atoms.begin() + index);
	return ptr;
}
