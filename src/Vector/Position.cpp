#include "Vector/Position.hpp"

md::BoundaryConditions md::Position::boundaryConditions;

double md::Position::distanceTo(Position::ConstPass position) const
{
    return boundaryConditions.distance(
        static_cast<Vector>(*this),
        static_cast<Vector>(position)
    );
}

std::pair<double, md::Vector> md::Position::distanceWithProjectionsTo(Position::ConstPass position) const
{
    return boundaryConditions.distanceWithProjections(
        static_cast<Vector>(*this),
        static_cast<Vector>(position)
    );
}

void md::Position::setBoundaryConditions(md::IDimensionsCondition* conditions[kDimensionalNumber])
{
    boundaryConditions.setConditions(conditions);
}
