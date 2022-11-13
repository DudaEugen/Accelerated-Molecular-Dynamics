#include <algorithm>
#include <unordered_map>
#include "Potential/EAM/APotentialEAM.hpp"

md::APotentialEAM::AEmbeddingTerm::AEmbeddingTerm(
    element first, element second, double cutRadius
) noexcept
    : elements{first, second}, cutRadius{cutRadius}
{
}

bool md::APotentialEAM::AEmbeddingTerm::isCorrectElements(const AtomPair& atomPair) const noexcept
{
    return (
		(
			atomPair.getFirst().chemElement == elements.first &&
			atomPair.getSecond().chemElement == elements.second
		) || (
			atomPair.getFirst().chemElement == elements.second &&
			atomPair.getSecond().chemElement == elements.first
		)
	);
}

double md::APotentialEAM::AEmbeddingTerm::getCutRadius() const noexcept
{
    return cutRadius;
}

md::APotentialEAM::APotentialEAM(
    APairPotential* pairPotential,
    const std::vector<const AEmbeddingTerm*>& terms
) noexcept
    : pairTerm{ pairPotential }, embeddingTerms{ terms }
{
}

md::APotentialEAM::~APotentialEAM()
{
    delete pairTerm;
    for (auto term: embeddingTerms)
    {
        delete term;
    }
}

double md::APotentialEAM::getCutRadius() const noexcept
{
    auto maxEmbeddingCutRadius = (*std::max_element(
        embeddingTerms.cbegin(),
        embeddingTerms.cend(),
        [](const AEmbeddingTerm* first, const AEmbeddingTerm* second)
        {
            return first->getCutRadius() < second->getCutRadius();
        }
    ))->getCutRadius();
    return std::max(maxEmbeddingCutRadius, pairTerm->getCutRadius());
}

void md::APotentialEAM::addAccelerations(NeighboursList& neighboursList) const
{
    auto embeddingAtoms = std::unordered_map<
        Atom*, std::vector<std::pair<AtomPair*, const APotentialEAM::AEmbeddingTerm*>>
    >();
    for (auto& atomPair: neighboursList.getPairs())
    {
        for (auto embeddingTerm: embeddingTerms)
        {
            if (embeddingTerm->isCorrectElements(atomPair))
            {
                auto pair = std::pair(&atomPair, embeddingTerm);
                embeddingAtoms[&atomPair.getFirst()].push_back(pair);
                embeddingAtoms[&atomPair.getSecond()].push_back(pair);
            }
        }
    }

    auto embeddingFunctionDerivatives = std::unordered_map<Atom*, double>();
    for (auto& [atom, pairs] : embeddingAtoms)
    {
        double summ = 0;
        for (auto pair: pairs)
        {
            summ += pair.second->computeTerm(*pair.first);
        }
        embeddingFunctionDerivatives[atom] = embeddingFunctionDerivative()(summ);
    }

    for (auto& [atom, pairs] : embeddingAtoms)
    {
        for (auto pair: pairs)
        {
            AtomPair& atomPair = *pair.first;
            Atom& first = atomPair.getFirst();
            Atom& second = atomPair.getSecond();
            Vector derivative = pair.second->computeTermDerivative(atomPair);
            first.addAcceleration(derivative / (embeddingFunctionDerivatives[atom] * first.mass));
            second.addAcceleration(-derivative / (embeddingFunctionDerivatives[atom] * second.mass));
        }
    }

    pairTerm->addAccelerations(neighboursList);
}
