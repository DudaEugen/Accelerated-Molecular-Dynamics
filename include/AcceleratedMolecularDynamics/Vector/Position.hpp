#pragma once
#ifndef TAHD_VELOCITY_H
#define TAHD_VELOCITY_H

#include "BoundaryConditions/BoundaryConditions.hpp"
#include "Vector/Vector.hpp"

namespace md
{
    class Position: public Vector
    {
        static BoundaryConditions boundaryConditions;
    public:
        using ConstPass = PassConstT<double, Position>;
        using Vector::Vector;

        static void setBoundaryConditions(IDimensionsCondition* conditions[kDimensionalNumber]);

        double sumSquares() const noexcept = delete;
		double absoluteValue() const noexcept = delete;

        double distanceTo(ConstPass postition) const;
        std::pair<double, Vector> distanceWithProjectionsTo(ConstPass postition) const;
    };
}

#endif  // TAHD_VELOCITY_H
