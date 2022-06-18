#include "BoundaryConditions/BoundaryConditions.hpp"
#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"
#include "IndexedZip.hpp"

md::BoundaryConditions::BoundaryConditions()
{
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        conditions_[i] = new InfiniteDimension();
    }
}

md::BoundaryConditions::BoundaryConditions(IDimensionsCondition* conditions[kDimensionalNumber])
{
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        conditions_[i] = conditions[i];
    }
}

md::BoundaryConditions::~BoundaryConditions()
{
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        delete conditions_[i];
    }
}

std::pair<double, md::Vector> md::BoundaryConditions::distanceWithProjections(
    Vector::ConstPass first, Vector::ConstPass second
) const
{
    Vector result;
    for (auto [index, resProj, firstProj, secondProj]: utils::zip::IndexedZip(result, first, second))
    {
        resProj = conditions_[index]->normalizeProjectionsDifference(firstProj, secondProj);
    }
    return std::pair(result.absoluteValue(), result);
}

double md::BoundaryConditions::distance(Vector::ConstPass first, Vector::ConstPass second) const
{
    auto [distance, _] = distanceWithProjections(first, second);
    return distance;
}

md::Vector md::BoundaryConditions::normolize(Vector::ConstPass vector) const
{
    Vector result;
    for (auto [index, resProj, proj]: utils::zip::IndexedZip(result, vector))
    {
        resProj = conditions_[index]->normalizeProjection(proj);
    }
    return result;
}
