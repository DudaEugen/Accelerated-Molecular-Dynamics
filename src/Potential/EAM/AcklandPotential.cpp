#include <cmath>
#include <numeric>
#include "Potential/EAM/AcklandPotential.hpp"

md::AcklandPotential::PairTerm::~PairTerm() {}

md::AcklandPotential::PairTerm::PairTerm(
    element first,
    element second,
    const std::array<Parameters, 6>& parameters
)
    : APairPotential{
        first,
        second,
        std::max_element(
            parameters.begin(),
            parameters.end(),
            [](const Parameters& f, const Parameters& s){ return f.distance < s.distance; }
        )->distance
    },
    parameters{ parameters }
{
}

double md::AcklandPotential::PairTerm::energy(double distance) const
{
	return std::accumulate(
        parameters.cbegin(),
        parameters.cend(),
        .0,
        [distance](double acc, const Parameters& params)
        {
            double diff = params.distance - distance;
            if (diff < 0)
            {
                return acc;
            }
            return acc + params.factor * std::pow(diff, 3);
        } 
    );
}

double md::AcklandPotential::PairTerm::derivative(double distance) const
{
    return std::accumulate(
        parameters.cbegin(),
        parameters.cend(),
        .0,
        [distance](double acc, const Parameters& params)
        {
            double diff = params.distance - distance;
            if (diff < 0)
            {
                return acc;
            }
            return acc + 3*params.factor * std::pow(diff, 2);
        } 
    );
}

md::AcklandPotential::EmbeddingTerm::~EmbeddingTerm() {}

md::AcklandPotential::EmbeddingTerm::EmbeddingTerm(
    element first,
    element second,
    const std::array<Parameters, 6>& parameters
)
    : AEmbeddingTerm{
        first,
        second,
        std::max_element(
            parameters.begin(),
            parameters.end(),
            [](const Parameters& f, const Parameters& s){ return f.distance < s.distance; }
        )->distance
    },
    parameters{ parameters }
{
}

double md::AcklandPotential::EmbeddingTerm::computeTerm(double distance) const
{
    return std::accumulate(
        parameters.cbegin(),
        parameters.cend(),
        .0,
        [distance](double acc, const Parameters& params)
        {
            double diff = params.distance - distance;
            if (diff < 0)
            {
                return acc;
            }
            return acc + params.factor * std::pow(diff, 3);
        } 
    );
}

double md::AcklandPotential::EmbeddingTerm::computeTermDerivative(double distance) const
{
    return std::accumulate(
        parameters.cbegin(),
        parameters.cend(),
        .0,
        [distance](double acc, const Parameters& params)
        {
            double diff = params.distance - distance;
            if (diff < 0)
            {
                return acc;
            }
            return acc + 3*params.factor * std::pow(diff, 2);
        } 
    );
}

std::function<double(double)> md::AcklandPotential::embeddingFunctionDerivative() const
{
    return [](double value){ return 0.5/std::sqrt(value); };
}

md::AcklandPotential::~AcklandPotential() {}

std::vector<const md::APairPotential*> md::AcklandPotential::constractPairTerms(
    const std::vector<PotentialParameters>& params
)
{
    std::vector<const APairPotential*> result;
    result.reserve(params.size());
    for (auto param: params)
    {
        result.push_back(new PairTerm(param.first, param.second, param.parameters));
    }
    return result;
}

std::vector<const md::AcklandPotential::AEmbeddingTerm*> md::AcklandPotential::constractEmbeddingTerms(
    const std::vector<PotentialParameters>& params
)
{
    std::vector<const AEmbeddingTerm*> result;
    result.reserve(params.size());
    for (auto param: params)
    {
        result.push_back(new EmbeddingTerm(param.first, param.second, param.parameters));
    }
    return result;
}

md::AcklandPotential::AcklandPotential(
    const std::vector<PotentialParameters>& pairTerms,
    const std::vector<PotentialParameters>& embeddingTerms
)
    : APotentialEAM(
        constractPairTerms(pairTerms),
        constractEmbeddingTerms(embeddingTerms)
    )
{
}
