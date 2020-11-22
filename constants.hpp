#pragma once
#ifndef TAHD_CONSTANTS_H
#define TAHD_CONSTANTS_H

#include <cmath>
#define DEBUG

#define DIMENSIONAL_NUMBER 3
#define MAX_DIMENSIONAL_FOR_VALUE_PASSING 3
constexpr double PI = 3.14159265359;
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

constexpr double K_BOLTZMANN = 1.38064852 * power(10, -23);
constexpr double N_AVOGADRO = 6.02214129 * power(10, 23);
constexpr double Q_ELEMENTARY = 1.60217662 * power(10, -19);
constexpr double H_PLANCK = 6.62606957 * power(10, -34);

#endif	//TAHD_CONSTANTS_H