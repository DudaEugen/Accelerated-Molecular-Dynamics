#include "BorderConditions.h"

BorderConditions::BorderConditions(ProjectionTuple& size, bool isPeriodicBorders[DIMENSIONAL_NUMBER])
	: size{ size }, type{}
{
	for (unsigned short int i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		type[i] = isPeriodicBorders[i] ? borderType::periodic : borderType::none;
	}
}

double BorderConditions::computeDistance(ProjectionTuple& projections)
{
	double squaredDistance = 0;
	for (unsigned short int i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		if (type[i] == borderType::periodic)
		{
			projections[i] -= size[i] * (
				((__int64)(2 * projections[i] / size[i])) -
				(__int64)(projections[i] / size[i])
				);
		}
		squaredDistance += projections[i] * projections[i];
	}

	return sqrt(squaredDistance);
}
