#define CPP_CUSTOM_ENUM
#include "constants/Elements.hpp"
#include <cmath>
#include <random>
#include <functional>
#include <chrono>

md::element_impl::AtomicMass::AtomicMass(const std::initializer_list<std::pair<double, unsigned>>& massDistribution)
    : massDistribution{ massDistribution }
{
}

unsigned md::element_impl::AtomicMass::average()
{
    double result = 0;
    for (auto [prob, mass]: massDistribution)
        result += prob * mass;
    return std::round(result);
}

unsigned md::element_impl::AtomicMass::random()
{
    static auto generator = std::bind( 
				std::uniform_real_distribution<double>(0, 1), 
				std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())
			);
    
    double x = generator();
    double probabilityAccumulator = 0;
    for (auto [prob, mass]: massDistribution)
    {
        probabilityAccumulator += prob;
        if (x < probabilityAccumulator)
            return mass;
    }
    return massDistribution.back().second;
}

md::ElementException::ElementException(const std::string& message) : std::runtime_error(message)
{
}

md::element md::parseElement(const std::string& title)
{
    for (element el: element_impl::allEnumValues())
        if(element_to_string(el) == title)
            return el;
    throw ElementException(std::string("Can't parse to element string: ") + title);
}

md::element_impl::AtomicMass md::atomicMass(const std::string& title)
{
    return atomicMass(parseElement(title));
}

std::uint8_t md::atomicNumber(const std::string& title)
{
    return atomicNumber(parseElement(title));
}
