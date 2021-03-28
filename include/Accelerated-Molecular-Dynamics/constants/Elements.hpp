#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include "custom enum/custom enum.hpp"
#include <vector>
#include <utility>

namespace md
{
	namespace element_impl
	{
		class Isotopes
		{
			const std::vector<std::pair<double, unsigned>> probabilitAndMass;
		public:
			Isotopes(const std::initializer_list<std::pair<double, unsigned>>& probabilitAndMass);
			unsigned compute_average_atomic_mass();
			unsigned generate_random_atomic_mass();
		};
	}

	CREATE_ENUM_F2(
		element,
		FUNCTION_HEADERS(std::uint8_t get_atomic_number, element_impl::Isotopes isotope_generator),
		VALUE_TUPLE(H, 1, element_impl::Isotopes({ {0.99985, 1}, {0.00015, 2} })),
		VALUE_TUPLE(He, 2, element_impl::Isotopes({ {0.0000014, 3}, {0.9999986, 4} })),
		VALUE_TUPLE(Li, 3, element_impl::Isotopes({ {0.075, 6}, {0.925, 7} })),
		VALUE_TUPLE(Be, 4, element_impl::Isotopes({ {1, 9} })),
		VALUE_TUPLE(B, 5, element_impl::Isotopes({ {0.198, 10}, {0.802, 11} })),
		VALUE_TUPLE(C, 6, element_impl::Isotopes({ {0.989, 12}, {0.011, 13} })),
		VALUE_TUPLE(O, 8, element_impl::Isotopes({ {0.99762, 16}, {0.00038, 17}, {0.002, 18} })),
		VALUE_TUPLE(Al, 13, element_impl::Isotopes({ {1, 27} })),
		VALUE_TUPLE(Si, 14, element_impl::Isotopes({ {0.9223, 28}, {0.0467, 29}, {0.031, 30} })),
		VALUE_TUPLE(Ar, 18, element_impl::Isotopes({ {0.00337, 36}, {0.00063, 38}, {0.996, 40} })),
		VALUE_TUPLE(Ti, 22, element_impl::Isotopes({ {0.08, 46}, {0.073, 47}, {0.738, 48}, {0.055, 49}, {0.054, 50} })),
		VALUE_TUPLE(Ni, 28, element_impl::Isotopes({ {0.6827, 58}, {0.261, 60}, {0.0113, 61}, {0.0359, 62}, {0.0091, 64} })),
		VALUE_TUPLE(Cu, 29, element_impl::Isotopes({ {0.6917, 63}, {0.3083, 65} })),
		VALUE_TUPLE(Au, 79, element_impl::Isotopes({ {1, 197} }))
	)

	class ElementException : public std::runtime_error {
	public:
		ElementException(const std::string& _Massage);
	};

	//functions throw ElementException if dont know values for this element
	// or element of enum does not have enumerator, that corresponding to title
	element parse(const std::string& title);
	element parse(char title);
	element parse(const char title[2]);
	element_impl::Isotopes isotope_generator(char title);
	element_impl::Isotopes isotope_generator(const char title[2]);
	element_impl::Isotopes isotope_generator(const std::string& title);
	std::uint8_t get_atomic_number(char title);
	std::uint8_t get_atomic_number(const char title[2]);
	std::uint8_t get_atomic_number(const std::string& title);
}

#endif	// TAHD_ELEMENTS_H
