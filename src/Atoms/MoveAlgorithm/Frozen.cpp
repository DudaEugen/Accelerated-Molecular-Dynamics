#include "Atoms/MoveAlgorithm/Frozen.hpp"

std::pair<md::Position, md::Vector> md::Frozen::move(
    Position::ConstPass position,
    Vector::ConstPass velocity,
    Vector::ConstPass acceleration,
    double deltaTime
) noexcept
{
    return std::pair(position, Vector{});
}
