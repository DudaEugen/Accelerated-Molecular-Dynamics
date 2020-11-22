#include "AtomGroup.hpp"

AtomGroup::AtomGroup(const size_t reservedNumber) : atoms{}
{
	atoms.reserve(reservedNumber);
}

void AtomGroup::reserve(const size_t number)
{
	atoms.reserve(number);
}

void AtomGroup::addAtom(Atom* atom)
{
	atoms.push_back(atom);
}

size_t AtomGroup::getAtomNumber() const noexcept { return atoms.size(); }

void AtomGroup::clearList() noexcept { atoms.resize(0); }

Atom& AtomGroup::operator [] (const size_t index)
{
	return *atoms[index];
}

Atom* AtomGroup::remove(const size_t index)
{
	Atom* ptr = atoms[index];
	atoms.erase(atoms.begin() + index);
	return ptr;
}
