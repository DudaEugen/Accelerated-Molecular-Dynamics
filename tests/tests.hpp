#pragma once
#ifndef TAHD_TESTS_H
#define TAHD_TESTS_H

#include <cassert>
#include <random>
#include <chrono>
#include <functional>
#include "Vector.hpp"

bool equal(double d1, double d2, int symbolCountAfterPoint = 12);

bool equal(md::Vector::ConstPass v1, md::Vector::ConstPass v2, int symbolCountAfterPoint = 12);

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

// tests

void testVector();

void testAtom();

void testSubstance();

void testMatrix();

void testAtomPair();

void testBorderConditions();

void testNeighboursList();

void testCellCollection();

void testZip();

void testDerivative();

#endif  // TAHD_TESTS_H
