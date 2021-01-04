#include "Potential/APairPotential.hpp"
#include "IndexedZip.hpp"

APairPotential::APairPotential(std::vector<AtomPair>* atomPairs, const std::size_t maxAtomPairTypes)
: APotential{ atomPairs }, indexes {}
{
	pairTypes.reserve(maxAtomPairTypes);
}

bool APairPotential::addPairType(const element first, const element second)
{
	bool isNew = true;
	for (const auto& pairType: pairTypes)
		if (pairType.first == first && pairType.second == second ||
			pairType.first == second && pairType.second == first)
		{
			isNew = false;
			break;
		}

	if (isNew)
		pairTypes.push_back(std::pair(first, second));
	return isNew;
}

void APairPotential::refreshAtomPairs()
{
	indexes.reserve(pairs->size());
	indexes.resize(0);
	for (const auto& atomPair : *pairs)
	{
		bool notFound = true;

		for (auto [index, pairType]: IndexedZip(std::as_const(pairTypes)))
		{
			if (pairType.first == atomPair.getFirst().chemElement && pairType.second == atomPair.getSecond().chemElement ||
				pairType.first == atomPair.getSecond().chemElement && pairType.second == atomPair.getFirst().chemElement)
			{
				indexes.push_back(index);
				notFound = false;
				break;
			}
		}

		if (notFound)
		{
			throw std::runtime_error("not found parameters for atom pair in pair potential");
		}
	}
}

double APairPotential::getCutRadius() const noexcept
{
	double max = 0;
	for (double cutRadius : rc)
		if (cutRadius > max)
			max = cutRadius;
	return max;
}
