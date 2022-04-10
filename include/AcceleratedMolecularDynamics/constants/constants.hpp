#pragma once
#ifndef TAHD_CONSTANTS_H
#define TAHD_CONSTANTS_H

#include <array>

namespace md
{
	inline constexpr uint8_t kDimensionalNumber = 3;

	// Generate mass for random isotope of element for an any atom if false
	// The probabilities for each isotope are determined in Elements.hpp
	inline constexpr bool kUseAverageAtomicMass = true;

	namespace constants_implementation
	{
		inline constexpr uint8_t kMaxSizeForValuePassing = 3;

		template<class T, class R>
		constexpr std::enable_if_t<
			(kDimensionalNumber * sizeof(T) > kMaxSizeForValuePassing * sizeof(void*)), 
		const std::remove_const_t<R>&> passType();

		template<class T, class R>
		constexpr std::enable_if_t<
			(kDimensionalNumber * sizeof(T) <= kMaxSizeForValuePassing * sizeof(void*)), 
		const std::remove_const_t<R>> passType();

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
				return 1 / power(v1, -v2);
			}
		}
	}
	/* Pass of R by value if sizeof(kDimensionalNumber * sizeof(T)) <= kMaxDimensionalForValuePassing * (void*)
	else pass const R& */
	template<class T, class R>
	using PassConstT = decltype(constants_implementation::passType<T, R>());

	template<class T>
	using PassConstArrayT = PassConstT<T, std::array<T, kDimensionalNumber>>;

	// Pphysical constants
	inline constexpr double kBoltzmann = 1.38064852 * constants_implementation::power(10, -23);
	inline constexpr double kAvogadro = 6.02214129 * constants_implementation::power(10, 23);
	inline constexpr double kElementaryCharge = 1.60217662 * constants_implementation::power(10, -19);
	inline constexpr double kPlank = 6.62606957 * constants_implementation::power(10, -34);
}

#endif	//TAHD_CONSTANTS_H
