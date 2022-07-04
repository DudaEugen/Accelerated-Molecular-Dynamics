#include "Vector/Position.hpp"
#include "BoundaryConditions/BoundaryConditions.hpp"
#include <algorithm>

double md::Position::distanceTo(Position::ConstPass position) const
{
    return BoundaryConditions::distance(*this, position);
}

std::pair<double, md::Vector::ConstPass> md::Position::distanceWithProjectionsTo(Position::ConstPass position) const
{
    return BoundaryConditions::distanceWithProjections(*this, position);
}

md::Vector md::Position::spaceSize()
{
    return BoundaryConditions::getSize();
}

void md::Position::normalize()
{
    const Position normalized = BoundaryConditions::normolize(*this);
    std::copy(normalized.begin(), normalized.end(), this->begin());
}

md::Position& md::Position::operator += (Vector::ConstPass other) noexcept
{
	Vector::operator+=(other);
	return *this;
}

md::Position& md::Position::operator -= (Vector::ConstPass other) noexcept
{
    Vector::operator-=(other);
	return *this;
}

md::Position md::operator + (Position::ConstPass position, Vector::ConstPass offset) noexcept
{
    Position result = position;
    result += offset;
    return result;
}

md::Position md::operator + (Vector::ConstPass offset, Position::ConstPass position) noexcept
{
    Position result = position + offset;
    return result;
}

md::Vector md::operator - (Position::ConstPass first, Position::ConstPass second) noexcept
{
    Position result = first;
    result -= static_cast<Vector>(second);
    return result;
}

md::Position md::operator - (Position::ConstPass position, Vector::ConstPass offset) noexcept
{
    Position result = position;
    result -= offset;
    return result;
}
