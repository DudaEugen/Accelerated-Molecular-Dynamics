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
        new md::Function(
            P0*utils::fcd::power<3>(X-P1)*utils::fcd::heavisideStep(X-P1) + 
            P2*utils::fcd::power<3>(X-P3)*utils::fcd::heavisideStep(X-P3) + 
            P4*utils::fcd::power<3>(X-P5)*utils::fcd::heavisideStep(X-P5) + 
            P6*utils::fcd::power<3>(X-P7)*utils::fcd::heavisideStep(X-P7) + 
            P8*utils::fcd::power<3>(X-P9)*utils::fcd::heavisideStep(X-P9) + 
            P10*utils::fcd::power<3>(X-P11)*utils::fcd::heavisideStep(X-P11),
            std::vector<double>({
                parameters[0].factor, parameters[0].distance,
                parameters[1].factor, parameters[1].distance,
                parameters[2].factor, parameters[2].distance,
                parameters[3].factor, parameters[3].distance,
                parameters[4].factor, parameters[4].distance,
                parameters[5].factor, parameters[5].distance
            })
        ),
        std::max_element(
            parameters.begin(),
            parameters.end(),
            [](const Parameters& f, const Parameters& s){ return f.distance < s.distance; }
        )->distance
    }
{
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

std::function<double(double)> md::AcklandPotential::embeddingFunction() const
{
    return [](double value){ return std::sqrt(value); };
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
