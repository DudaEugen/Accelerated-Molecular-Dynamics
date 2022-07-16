#include <functional>
#include "PartOfSystem/Cell.hpp"

const std::vector<std::reference_wrapper<md::Atom>>& md::Cell::getAtoms() const noexcept
{
	return atoms;
}

void md::Cell::addAtom(Atom& atom)
{
	atoms.push_back(std::ref(atom));
}

void md::Cell::clear() noexcept
{
	atoms.clear();
}
