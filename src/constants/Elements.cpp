#define CPP_CUSTOM_ENUM
#include "constants/Elements.hpp"
#include <cmath>
#include <random>
#include <functional>
#include <chrono>

md::element_impl::Isotopes::Isotopes(const std::initializer_list<std::pair<double, unsigned>>& probabilitAndMass)
    : probabilitAndMass{ probabilitAndMass }
{
}

unsigned md::element_impl::Isotopes::compute_average_atomic_mass()
{
    double result = 0;
    for (auto [prob, mass]: probabilitAndMass)
        result += prob * mass;
    return std::round(result);
}

unsigned md::element_impl::Isotopes::generate_random_atomic_mass()
{
    static auto generator =  std::bind( 
				std::uniform_real_distribution<double>(0, 1), 
				std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())
			);
    
    double x = generator();
    double probabilityAccumulator = 0;
    for (auto [prob, mass]: probabilitAndMass)
    {
        probabilityAccumulator += prob;
        if (x < probabilityAccumulator)
            return mass;
    }
    return probabilitAndMass.back().second;
}

md::ElementException::ElementException(const std::string& _Massage) : std::runtime_error(_Massage)
{
}

md::element md::parse(const std::string& title)
{
    for (element el: element_impl::allEnumValues())
        if(element_to_string(el) == title)
            return el;
    throw ElementException(std::string("Can't parse to element string: ") + title);
}

md::element md::parse(char title)
{
	return parse(std::string{title});
}

md::element md::parse(const char title[2])
{
    return parse(std::string{title, 2});
}

md::element_impl::Isotopes md::isotope_generator(char title)
{
    return isotope_generator(parse(title));
}

md::element_impl::Isotopes md::isotope_generator(const char title[2])
{
    return isotope_generator(parse(title));
}

md::element_impl::Isotopes md::isotope_generator(const std::string& title)
{
    return isotope_generator(parse(title));
}

std::uint8_t md::get_atomic_number(char title)
{
    return get_atomic_number(title);
}

std::uint8_t md::get_atomic_number(const char title[2])
{
    return get_atomic_number(title);
}

std::uint8_t md::get_atomic_number(const std::string& title)
{
    return get_atomic_number(title);
}
