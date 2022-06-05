#pragma once
#ifndef TAHD_PERIODIC_DIMENSION_H
#define TAHD_PERIODIC_DIMENSION_H

#include "BoundaryConditions/DimensionsCondition/IDimensionsCondition.hpp"

namespace md
{
    class PeriodicDimension: public IDimensionsCondition
    {
        double size;
    public:
        PeriodicDimension(double size) noexcept;
        double normalizeProjection(double coordinate) const override;
        double normalizeProjectionsDifference(double projectionFirst, double projectionSecond) const override;
        ~PeriodicDimension() = default;
    };
}

#endif  //TAHD_PERIODIC_DIMENSION_H
