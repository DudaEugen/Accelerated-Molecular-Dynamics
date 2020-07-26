#include "APairPotential.h"

APairPotential::APairPotential(AtomicSystem* s, const std::size_t maxAtomPairTypes)
: APotential{ s }, indexes {}
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
		pairTypes.push_back(std::make_pair(first, second));
	return isNew;
}

void APairPotential::refreshAtomPairs()
{
	std::vector<AtomPair>& atomPairs = system->getAtomPairs();
	indexes.reserve(atomPairs.size());
	indexes.resize(0);
	for (const auto& atomPair : atomPairs)
	{
		bool notFound = true;

		for (std::size_t i = 0; i < pairTypes.size(); ++i)
		{
			if (pairTypes[i].first == atomPair.getFirst().chemElement && pairTypes[i].second == atomPair.getSecond().chemElement ||
				pairTypes[i].first == atomPair.getSecond().chemElement && pairTypes[i].second == atomPair.getFirst().chemElement)
			{
				indexes.push_back(i);
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

double APairPotential::getCutRadius() const
{
	double max = 0;
	for (double cutRadius : rc)
		if (cutRadius > max)
			max = cutRadius;
	return max;
}