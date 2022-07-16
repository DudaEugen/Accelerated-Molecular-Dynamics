#pragma once
#ifndef TAHD_PERIODIC_DIMENSION_H
#define TAHD_PERIODIC_DIMENSION_H

#include "BoundaryConditions/DimensionsCondition/IDimensionsCondition.hpp"

namespace md
{
    class PeriodicDimension: public IDimensionsCondition
    {
        double minimalProjection;
        double size;
    public:
        PeriodicDimension(double size, double start = 0) noexcept;
        double getMinimalProjectionValue() const noexcept;
        double getSize() const noexcept override;
        double normalizeProjection(double coordinate) const override;
        double normalizeProjectionsDifference(double projectionFirst, double projectionSecond) const override;
        ~PeriodicDimension() = default;
    };
}

#endif  //TAHD_PERIODIC_DIMENSION_H
