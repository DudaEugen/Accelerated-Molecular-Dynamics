#include <functional>
#include "PartOfSystem/Cell.hpp"

std::vector<md::Atom*>& md::Cell::getAtoms() noexcept
{
	return atoms;
}

void md::Cell::addAtom(Atom& atom)
{
	atoms.push_back(&atom);
}

void md::Cell::clear() noexcept
{
	atoms.clear();
}
