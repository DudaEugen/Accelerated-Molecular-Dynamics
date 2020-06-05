#include "BorderConditions.h"

BorderConditions::BorderConditions(Vector::ConstVectorPass size, borderType borders[DIMENSIONAL_NUMBER])
	: size{ size }
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		type[i] = borders[i];
	}
}

double BorderConditions::operator() (Vector& projectionsDifference) const
{
	double squaredDistance = 0;
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		if (type[i] == borderType::periodic)
		{
			projectionsDifference[i] -= size[i] * (
				((int64_t)(2 * projectionsDifference[i] / size[i])) -
				(int64_t)(projectionsDifference[i] / size[i])
				);
		}
		squaredDistance += projectionsDifference[i] * projectionsDifference[i];
	}
	return sqrt(squaredDistance);
}
