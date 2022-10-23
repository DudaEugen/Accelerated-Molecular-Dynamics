#pragma once
#ifndef TAHD_TESTS_H
#define TAHD_TESTS_H

#include <cassert>
#include "features/compare.hpp"
#include "features/random.hpp"
#include "features/reset.hpp"

void testVector();

void testParallel();

void testElement();

void testMoveAlgorithm();

void testAtom();

void testSubstance();

void testBoundaryConditions();

void testMatrix();

void testAtomPair();

void testCell();

void testZip();

void testDerivative();

#endif  // TAHD_TESTS_H
