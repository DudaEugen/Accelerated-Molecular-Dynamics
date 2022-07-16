#include "BoundaryConditions/BoundaryConditions.hpp"
#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"
#include "Zip.hpp"
#include "IndexedZip.hpp"

md::BoundaryConditions::Conditions md::BoundaryConditions::conditions_;

md::BoundaryConditions::Conditions::Conditions()
{
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        conditions_[i] = new InfiniteDimension();
    }
}

md::BoundaryConditions::Conditions::~Conditions()
{
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        delete conditions_[i];
    }
}

void md::BoundaryConditions::Conditions::setConditions(IDimensionsCondition* conditions[kDimensionalNumber]) noexcept
{
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        delete conditions_[i];
        conditions_[i] = conditions[i];
    }
}

md::IDimensionsCondition* md::BoundaryConditions::Conditions::operator[](std::uint8_t index) const
{
    return conditions_[index];
}

void md::BoundaryConditions::setConditions(IDimensionsCondition* conditions[kDimensionalNumber])
{
    conditions_.setConditions(conditions);
}

std::pair<double, md::Vector::ConstPass> md::BoundaryConditions::distanceWithProjections(
    Position::ConstPass first, Position::ConstPass second
)
{
    Vector result;
    for (auto [index, resProj, firstProj, secondProj]: utils::zip::IndexedZip(result, first, second))
    {
        resProj = conditions_[index]->normalizeProjectionsDifference(firstProj, secondProj);
    }
    return std::pair(result.absoluteValue(), result);
}

double md::BoundaryConditions::distance(Position::ConstPass first, Position::ConstPass second)
{
    auto [distance, _] = distanceWithProjections(first, second);
    return distance;
}

md::Position md::BoundaryConditions::normolize(Position::ConstPass position)
{
    Position result;
    for (auto [index, resProj, proj]: utils::zip::IndexedZip(result, position))
    {
        resProj = conditions_[index]->normalizeProjection(proj);
    }
    return result;
}

md::Position md::BoundaryConditions::getMinimalPosition() noexcept
{
    Position position;
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        position[i] = conditions_[i]->getMinimalProjectionValue();
    }
    return position;
}

md::Vector md::BoundaryConditions::getSize() noexcept
{
    Vector size;
    for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
    {
        size[i] = conditions_[i]->getSize();
    }
    return size;
}
