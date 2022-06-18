#pragma once
#ifndef TAHD_INTERFACE_MOVE_ALGORITHM_H
#define TAHD_INTERFACE_MOVE_ALGORITHM_H

#include <utility>
#include "Vector/Vector.hpp"

namespace md
{
    class IMoveAlgorithm
    {
    public:
        // return: std::pair<position, velocity>
        virtual std::pair<Vector, Vector> move(
            Vector::ConstPass position,
            Vector::ConstPass velocity,
            Vector::ConstPass acceleration,
            double deltaTime
        ) noexcept = 0;
        
        virtual ~IMoveAlgorithm() = 0;
    };
}

#endif	//TAHD_INTERFACE_MOVE_ALGORITHM_H
