#pragma once
#ifndef TAHD_FROZEN_H
#define TAHD_FROZEN_H

#include "IMoveAlgorithm.hpp"

namespace md
{
    class Frozen: public IMoveAlgorithm
    {
    public:
        Frozen() noexcept = default;

        std::pair<md::Position, md::Vector> move(
            Position::ConstPass position,
            Vector::ConstPass velocity,
            Vector::ConstPass acceleration,
            double deltaTime
        ) noexcept;

        ~Frozen() = default;
    };
}

#endif	//TAHD_FROZEN_H
