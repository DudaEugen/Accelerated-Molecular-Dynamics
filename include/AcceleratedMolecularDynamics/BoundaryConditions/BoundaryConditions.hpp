#pragma once
#ifndef TAHD_BOUNDARY_CONDITIONS_H
#define TAHD_BOUNDARY_CONDITIONS_H

#include <utility>
#include "constants/constants.hpp"
#include "BoundaryConditions/DimensionsCondition/IDimensionsCondition.hpp"
#include "Vector/Vector.hpp"

namespace md
{
    class BoundaryConditions
    {
    private:
        IDimensionsCondition* conditions_[kDimensionalNumber];

    public:
        BoundaryConditions();
        BoundaryConditions(IDimensionsCondition* conditions[kDimensionalNumber]);
        BoundaryConditions(const BoundaryConditions&) = delete;
        BoundaryConditions(BoundaryConditions&&) = delete;
        BoundaryConditions& operator=(const BoundaryConditions&) = delete;
        BoundaryConditions& operator=(BoundaryConditions&&) = delete;
        ~BoundaryConditions();

        std::pair<double, Vector> distanceWithProjections(Vector::ConstPass first, Vector::ConstPass second) const;
        double distance(Vector::ConstPass first, Vector::ConstPass second) const;
        Vector normolize(Vector::ConstPass vector) const;

        void setConditions(IDimensionsCondition* conditions[kDimensionalNumber]);
    };
}

#endif  //TAHD_BOUNDARY_CONDITIONS_H
