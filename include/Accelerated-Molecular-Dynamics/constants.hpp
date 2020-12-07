#pragma once
#ifndef TAHD_CONSTANTS_H
#define TAHD_CONSTANTS_H

#include <array>

inline constexpr uint8_t DIMENSIONAL_NUMBER = 3;
inline constexpr uint8_t MAX_DIMENSIONAL_FOR_VALUE_PASSING = 3;

namespace
{
	template<class T, class R>
	constexpr std::enable_if_t<
		(DIMENSIONAL_NUMBER * sizeof(T) > MAX_DIMENSIONAL_FOR_VALUE_PASSING * sizeof(void*)), 
	R&> pass_dimensional_number_elements_type();

	template<class T, class R>
	constexpr std::enable_if_t<
		(DIMENSIONAL_NUMBER * sizeof(T) <= MAX_DIMENSIONAL_FOR_VALUE_PASSING * sizeof(void*)), 
	R> pass_dimensional_number_elements_type();
}
/* Pass of R by value if sizeof(DIMENSIONAL_NUMBER * sizeof(T)) <= MAX_DIMENSIONAL_FOR_VALUE_PASSING * (void*)
 don't use PassT for change R (pass R& to function for this) */
template<class T, class R>
using PassT = decltype(pass_dimensional_number_elements_type<T, R>());

template<class T>
using ConstPassArrayT = PassT<T, const std::array<T, DIMENSIONAL_NUMBER>>;

//physical constants
constexpr double power(unsigned int v1, int v2)
{
	if (v2 == 0)
	{
		return 1;
	}
	else if (v2 > 0)
	{
		return v1 * power(v1, v2 - 1);
	}
	else
	{
		return 1 / power(v1, (unsigned int) -v2);
	}
}

inline constexpr double K_BOLTZMANN = 1.38064852 * power(10, -23);
inline constexpr double N_AVOGADRO = 6.02214129 * power(10, 23);
inline constexpr double Q_ELEMENTARY = 1.60217662 * power(10, -19);
inline constexpr double H_PLANCK = 6.62606957 * power(10, -34);

#endif	//TAHD_CONSTANTS_H
