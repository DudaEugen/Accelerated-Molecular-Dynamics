#pragma once
#ifndef TAHD_VELOCITY_VERLET_H
#define TAHD_VELOCITY_VERLET_H

#include "IMoveAlgorithm.hpp"

namespace md
{
    class VelocityVerlet: public IMoveAlgorithm
    {
        Vector previousStepAcceleration;
        bool isFirstStep;
    public:
        VelocityVerlet() noexcept;

        std::pair<Position, Vector> move(
            Position::ConstPass position,
            Vector::ConstPass velocity,
            Vector::ConstPass acceleration,
            double deltaTime
        ) noexcept;

        ~VelocityVerlet() = default;
    };
}

#endif	//TAHD_VELOCITY_VERLET_H
