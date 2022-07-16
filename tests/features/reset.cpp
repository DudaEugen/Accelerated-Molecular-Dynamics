#include "features/reset.hpp"
#include "constants/constants.hpp"
#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"
#include "BoundaryConditions/BoundaryConditions.hpp"

void resetBoundaryConditions()
{
	md::IDimensionsCondition* conditions[md::kDimensionalNumber];
	for (uint8_t i = 0; i < md::kDimensionalNumber; ++i) {
		conditions[i] = new md::InfiniteDimension();
	}
	md::BoundaryConditions::setConditions(conditions);
}
