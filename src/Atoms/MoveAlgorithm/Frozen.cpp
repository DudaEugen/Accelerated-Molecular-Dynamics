#include "Atoms/MoveAlgorithm/Frozen.hpp"

std::pair<md::Vector, md::Vector> md::Frozen::move(
    Vector::ConstPass position,
    Vector::ConstPass velocity,
    Vector::ConstPass acceleration,
    double deltaTime
) noexcept
{
    return std::pair(position, Vector{});
}
