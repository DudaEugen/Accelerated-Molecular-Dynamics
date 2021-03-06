#pragma once
#ifndef TAHD_CONSTANTS_H
#define TAHD_CONSTANTS_H

#include <array>

namespace md
{
	inline constexpr uint8_t kDimensionalNumber = 3;
	inline constexpr uint8_t kMaxDimensionalForValuePassing = 3;

	namespace
	{
		template<class T, class R>
		constexpr std::enable_if_t<
			(kDimensionalNumber * sizeof(T) > kMaxDimensionalForValuePassing * sizeof(void*)), 
		R&> passkDimensionalNumberElementsType();

		template<class T, class R>
		constexpr std::enable_if_t<
			(kDimensionalNumber * sizeof(T) <= kMaxDimensionalForValuePassing * sizeof(void*)), 
		R> passkDimensionalNumberElementsType();

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
	}
	/* Pass of R by value if sizeof(kDimensionalNumber * sizeof(T)) <= kMaxDimensionalForValuePassing * (void*)
	don't use PassT for change R (pass R& to function for this) */
	template<class T, class R>
	using PassT = decltype(passkDimensionalNumberElementsType<T, R>());

	template<class T>
	using ConstPassArrayT = PassT<T, const std::array<T, kDimensionalNumber>>;

	//physical constants
	inline constexpr double kBoltzmann = 1.38064852 * power(10, -23);
	inline constexpr double kAvogadro = 6.02214129 * power(10, 23);
	inline constexpr double kElementaryCharge = 1.60217662 * power(10, -19);
	inline constexpr double kPlank = 6.62606957 * power(10, -34);
}

#endif	//TAHD_CONSTANTS_H
