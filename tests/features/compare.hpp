#pragma once
#ifndef TAHD_TESTS_COMPARE_H
#define TAHD_TESTS_COMPARE_H

#include <vector>
#include "Vector/Vector.hpp"

bool equal(double d1, double d2, int symbolCountAfterPoint = 12);

bool equal(md::Vector::ConstPass v1, md::Vector::ConstPass v2, int symbolCountAfterPoint = 12);

bool equalAll(const std::vector<md::Vector>& vectors, int symbolCountAfterPoint = 12);

template<class T>
bool contain(const std::vector<T>& container, T value)
{
    for (auto el: container)
    {
        if (el == value)
            return true;
    }
    return false;
}

#endif  // TAHD_TESTS_COMPARE_H
