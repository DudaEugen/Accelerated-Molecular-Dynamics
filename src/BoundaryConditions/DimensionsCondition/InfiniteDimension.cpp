#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"

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
