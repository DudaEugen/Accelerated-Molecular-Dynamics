#pragma once
#ifndef TAHD_INFINITE_DIMENSION_H
#define TAHD_INFINITE_DIMENSION_H

#include "BoundaryConditions/DimensionsCondition/IDimensionsCondition.hpp"

namespace md
{
    class InfiniteDimension: public IDimensionsCondition
    {
    public:
        InfiniteDimension() noexcept = default;
        double normalizeProjection(double coordinate) const override;
        double normalizeProjectionsDifference(double projectionFirst, double projectionSecond) const override;
        ~InfiniteDimension() = default;
    };
}

#endif  //TAHD_INFINITE_DIMENSION_H
