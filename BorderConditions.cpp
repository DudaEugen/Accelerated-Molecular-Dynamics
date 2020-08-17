#include "BorderConditions.h"

BorderConditions::BorderConditions(Vector::ConstVectorPass size, borderType borders[DIMENSIONAL_NUMBER]) noexcept
	: size{ size }
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		type[i] = borders[i];
	}
}

const BorderConditions::borderType* BorderConditions::getBorderTypes() const noexcept { return type; }

Vector::ConstVectorPass BorderConditions::getSize() const noexcept { return size; }

double BorderConditions::operator() (Vector& projectionsDifference) const noexcept
{
	double squaredDistance = 0;
	double ratioProjToSize;
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		if (type[i] == borderType::periodic)
		{
			ratioProjToSize = projectionsDifference[i] / size[i];
			projectionsDifference[i] -= size[i] * (
				static_cast<int64_t>(2 * ratioProjToSize) -
				static_cast<int64_t>(ratioProjToSize)
			);
		}
		squaredDistance += projectionsDifference[i] * projectionsDifference[i];
	}
	return sqrt(squaredDistance);
}
