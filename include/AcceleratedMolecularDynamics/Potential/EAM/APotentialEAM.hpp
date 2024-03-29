#pragma once
#ifndef TAHD_ABSTRACT_POTENTIAL_EAM_H
#define TAHD_ABSTRACT_POTENTIAL_EAM_H

#include <functional>
#include "Potential/PairPotential/APairPotential.hpp"

namespace md
{
	class APotentialEAM: public APotential
	{
	protected:
        class AEmbeddingTerm
        {
            double cutRadius;
            std::pair<element, element> elements;
        public:
            AEmbeddingTerm(element first, element second, double cutRadius) noexcept;
            virtual ~AEmbeddingTerm() = 0;

            bool isCorrectElements(const AtomPair& atomPair) const noexcept;
            double getCutRadius() const noexcept;
            virtual double computeTerm(const AtomPair& atomPair) const = 0;
            virtual double computeTermDerivative(const AtomPair& atomPair) const = 0;
        };

		const std::vector<const APairPotential*> pairTerms;
        const std::vector<const AEmbeddingTerm*> embeddingTerms;

        virtual std::function<double(double)> embeddingFunctionDerivative() const = 0;
	public:
		APotentialEAM(
            const std::vector<const APairPotential*>& pairPotentials,
            const std::vector<const AEmbeddingTerm*>& terms
        ) noexcept;
		virtual ~APotentialEAM();
        void addAccelerations(NeighboursList& neighboursList) const override;
		double getCutRadius() const noexcept override;
	};
}

#endif	//TAHD_ABSTRACT_POTENTIAL_EAM_H
