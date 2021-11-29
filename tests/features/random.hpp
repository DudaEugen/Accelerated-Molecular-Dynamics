#pragma once
#ifndef TAHD_TESTS_RANDOM_H
#define TAHD_TESTS_RANDOM_H

#include <chrono>
#include <functional>
#include <random>
#include "Vector.hpp"

template<int MIN = -100, int MAX = 100>
double random()
{
	static auto r =  std::bind( 
				std::uniform_real_distribution<double>(MIN, MAX), 
				std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())
			);
	return r();
}

template<int MIN = -100, int MAX = 100>
md::Vector randomVector()
{
	md::Vector v;
	for (double& projection: v)
		projection = random<MIN, MAX>();
	return v;
}

#endif  // TAHD_TESTS_RANDOM_H
