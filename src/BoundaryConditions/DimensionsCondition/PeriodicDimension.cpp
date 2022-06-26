#include "BoundaryConditions/DimensionsCondition/PeriodicDimension.hpp"
#include <cmath>

md::PeriodicDimension::PeriodicDimension(double size) noexcept
    : size{size}
{
}

double md::PeriodicDimension::getSize() const noexcept
{
    return size;
}

double md::PeriodicDimension::normalizeProjection(double coordinate) const
{
    return coordinate - static_cast<int>(std::floor(coordinate / size)) * size;
}

double md::PeriodicDimension::normalizeProjectionsDifference(
    double projectionFirst, double projectionSecond
) const
{
    double difference = projectionFirst - projectionSecond;
    return difference - size * (
        static_cast<int>(std::trunc(2*difference/size)) - 
        static_cast<int>(std::trunc(difference/size))
    );
}
