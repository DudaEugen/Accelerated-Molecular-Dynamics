#pragma once
#ifndef TAHD_TESTS_RANDOM_H
#define TAHD_TESTS_RANDOM_H

#include <chrono>
#include <functional>
#include <random>
#include "Vector/Position.hpp"
#include "Vector/Vector.hpp"

template<int MIN = -100, int MAX = 100>
double randomDouble()
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
		projection = randomDouble<MIN, MAX>();
	return v;
}

template<int MIN = -100, int MAX = 100>
md::Position randomPosition()
{
	md::Position position;
	for (double& projection: position)
		projection = randomDouble<MIN, MAX>();
	return position;
}

#endif  // TAHD_TESTS_RANDOM_H
