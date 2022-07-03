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
        static Vector spaceSize();

		Position& operator += (Vector::ConstPass other) noexcept;
		Position& operator -= (Vector::ConstPass other) noexcept;

		Position& operator *= (double factor) = delete;
		Position& operator /= (double divider) = delete;
        Position& operator += (Position::ConstPass other) = delete;
        Position& operator -= (Position::ConstPass other) = delete;
        double sumSquares() const noexcept = delete;
		double absoluteValue() const noexcept = delete;

        double distanceTo(ConstPass postition) const;
        std::pair<double, Vector::ConstPass> distanceWithProjectionsTo(ConstPass postition) const;
        void normalize();
    };

    Position operator + (Position::ConstPass position, Vector::ConstPass offset) noexcept;
    Position operator + (Vector::ConstPass offset, Position::ConstPass position) noexcept;
	Vector operator - (Position::ConstPass first, Position::ConstPass second) noexcept;
    Position operator - (Position::ConstPass position, Vector::ConstPass offset) noexcept;

    Position operator + (Position::ConstPass first, Position::ConstPass second) = delete;
	Position operator * (Position::ConstPass vector, double factor) = delete;
	Position operator * (double factor, Position::ConstPass vector) = delete;
	Position operator / (Position::ConstPass vector, double divider) = delete;
    Position operator - (Vector::ConstPass offset, Position::ConstPass position) = delete;
}

#endif  // TAHD_VELOCITY_H
