#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include "custom enum/custom enum.hpp"
#include <array>

namespace md
{
	CREATE_ENUM_F2(
		element,
		FUNCTION_HEADERS(std::uint8_t get_atomic_number, unsigned get_atomic_mass),
		VALUE_TUPLE(H, 1, 1),
		VALUE_TUPLE(He, 2, 4),
		VALUE_TUPLE(Li, 3, 7),
		VALUE_TUPLE(Be, 4, 9),
		VALUE_TUPLE(B, 5, 11),
		VALUE_TUPLE(C, 6, 12),
		VALUE_TUPLE(O, 8, 16),
		VALUE_TUPLE(Al, 13, 27),
		VALUE_TUPLE(Si, 14, 28),
		VALUE_TUPLE(Ar, 18, 40),
		VALUE_TUPLE(Ti, 22, 48),
		VALUE_TUPLE(Ni, 28, 59),
		VALUE_TUPLE(Cu, 29, 64),
		VALUE_TUPLE(Au, 79, 197)
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
	unsigned get_atomic_mass(char title);
	unsigned get_atomic_mass(const char title[2]);
	unsigned get_atomic_mass(const std::string& title);
	std::uint8_t get_atomic_number(char title);
	std::uint8_t get_atomic_number(const char title[2]);
	std::uint8_t get_atomic_number(const std::string& title);

	constexpr std::array<element, element_impl::kMaxEnumValue+1> all_elements()
	{
		std::array<element, element_impl::kMaxEnumValue+1> result{};
		for (std::uint8_t i = 0; i <= element_impl::kMaxEnumValue; ++i)
		{
			result[i] = element{i};
		}
		return result;
	}
}

#endif	// TAHD_ELEMENTS_H
