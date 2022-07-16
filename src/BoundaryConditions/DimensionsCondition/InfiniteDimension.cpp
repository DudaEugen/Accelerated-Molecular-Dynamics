#include <limits>
#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"

double md::InfiniteDimension::getMinimalProjectionValue() const noexcept
{
    return -std::numeric_limits<double>::infinity();
}

double md::InfiniteDimension::getSize() const noexcept
{
    return std::numeric_limits<double>::infinity();
}

double md::InfiniteDimension::normalizeProjection(double coordinate) const
{
    return coordinate;
}

double md::InfiniteDimension::normalizeProjectionsDifference(
    double projectionFirst, double projectionSecond
) const
{
    return projectionFirst - projectionSecond;
}
