#pragma once
#ifndef TAHD_ACKLAND_POTENTIAL_H
#define TAHD_ACKLAND_POTENTIAL_H

#include <array>
#include <utility>
#include "Potential/EAM/APotentialEAM.hpp"

namespace md
{
    class AcklandPotential: public APotentialEAM
    {
    public:
        struct Parameters
        {
            double factor;
            double distance;
        };
        struct PotentialParameters
        {
            element first;
            element second;
            std::array<Parameters, 6> parameters;
        };

    private:
        class PairTerm: public APairPotential
        {
            std::array<Parameters, 6> parameters;

        protected:
            double derivative(const AtomPair& pair) const override;
        public:
            PairTerm(element first, element second, const std::array<Parameters, 6>& parameters);
            ~PairTerm() override;
        };

        class EmbeddingTerm: public APotentialEAM::AEmbeddingTerm
        {
            std::array<Parameters, 6> parameters;

        public:
            EmbeddingTerm(
                element first,
                element second,
                const std::array<Parameters, 6>& parameters
            );
            ~EmbeddingTerm() override;

            double computeTerm(const AtomPair& atomPair) const override;
            double computeTermDerivative(const AtomPair& atomPair) const override;
        };

        std::function<double(double)> embeddingFunctionDerivative() const override;

        static std::vector<const APairPotential*> constractPairTerms(
            const std::vector<PotentialParameters>& params
        );
        static std::vector<const AEmbeddingTerm*> constractEmbeddingTerms(
            const std::vector<PotentialParameters>& params
        );
    public:
        AcklandPotential(
            const std::vector<PotentialParameters>& pairTerms,
            const std::vector<PotentialParameters>& embeddingTerms
        );
        ~AcklandPotential() override;
    };
}

#endif  //TAHD_ACKLAND_POTENTIAL_H
