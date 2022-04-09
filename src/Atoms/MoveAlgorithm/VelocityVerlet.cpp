#include "Atoms/MoveAlgorithm/VelocityVerlet.hpp"
#include <cmath>

md::VelocityVerlet::VelocityVerlet() noexcept
    : previousStepAcceleration{}, isFirstStep{true}
{
}

std::pair<md::Vector, md::Vector> md::VelocityVerlet::move(
    Vector::ConstPass position,
    Vector::ConstPass velocity,
    Vector::ConstPass acceleration,
    double deltaTime
) noexcept
{
    auto result = std::pair{position, velocity};
    result.first += velocity * deltaTime + 0.5 * acceleration * std::pow(deltaTime, 2);
    if (!isFirstStep)  // [[likely]] (c++20)
        result.second += 0.5 * (acceleration + previousStepAcceleration) * deltaTime;
    else               // [[unlikely]] (c++20)
        result.second += acceleration * deltaTime;

    previousStepAcceleration = acceleration;
    isFirstStep = false;

    return result;
}
