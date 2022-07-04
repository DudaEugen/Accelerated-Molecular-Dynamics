#pragma once
#ifndef TAHD_BOUNDARY_CONDITIONS_H
#define TAHD_BOUNDARY_CONDITIONS_H

#include <utility>
#include "constants/constants.hpp"
#include "BoundaryConditions/DimensionsCondition/IDimensionsCondition.hpp"
#include "Vector/Position.hpp"

namespace md
{
    class BoundaryConditions
    {
    private:
        struct Conditions
        {
            IDimensionsCondition* conditions_[kDimensionalNumber];

            Conditions();
            void setConditions(IDimensionsCondition* conditions[kDimensionalNumber]) noexcept;
            IDimensionsCondition* operator[](std::uint8_t index) const;
            ~Conditions();
        };
        static Conditions conditions_;

    public:
        BoundaryConditions(const BoundaryConditions&) = delete;
        BoundaryConditions(BoundaryConditions&&) = delete;
        BoundaryConditions& operator=(const BoundaryConditions&) = delete;
        BoundaryConditions& operator=(BoundaryConditions&&) = delete;
        ~BoundaryConditions() = delete;

        static void setConditions(IDimensionsCondition* conditions[kDimensionalNumber]);

        static std::pair<double, Vector::ConstPass> distanceWithProjections(
            Position::ConstPass first, Position::ConstPass second
        );
        static double distance(Position::ConstPass first, Position::ConstPass second);
        static Position normolize(Position::ConstPass position);

        static Vector getSize();
    };
}

#endif  //TAHD_BOUNDARY_CONDITIONS_H
