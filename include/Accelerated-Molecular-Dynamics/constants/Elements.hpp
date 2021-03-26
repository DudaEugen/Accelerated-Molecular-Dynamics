#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include "custom enum/custom enum.hpp"

namespace md
{
	CREATE_ENUM_F2(
		element,
		FUNCTION_HEADERS(std::uint8_t get_atomic_number, int get_atomic_mass),
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
}

#endif	// TAHD_ELEMENTS_H
