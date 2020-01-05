#include "BorderConditions.h"

BorderConditions::BorderConditions(Vector& size, bool isPeriodicBorders[DIMENSIONAL_NUMBER])
	: size{ size }, type{}
{
#if DIMENSIONAL_NUMBER == 3
	type[0] = isPeriodicBorders[0] ? borderType::periodic : borderType::none;
	type[1] = isPeriodicBorders[1] ? borderType::periodic : borderType::none;
	type[2] = isPeriodicBorders[2] ? borderType::periodic : borderType::none;
#elif DIMENSIONAL_NUMBER == 2
	type[0] = isPeriodicBorders[0] ? borderType::periodic : borderType::none;
	type[1] = isPeriodicBorders[1] ? borderType::periodic : borderType::none;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		type[i] = isPeriodicBorders[i] ? borderType::periodic : borderType::none;
	}
#endif
}

double BorderConditions::computeDistance(Vector& projectionsDifference) const
{
	double squaredDistance = 0;
#if DIMENSIONAL_NUMBER == 3
	double d[3];
	d[0] = type[0] == borderType::periodic ? projectionsDifference[0] / size[0] : 0;
	d[1] = type[1] == borderType::periodic ? projectionsDifference[1] / size[1] : 0;
	d[2] = type[2] == borderType::periodic ? projectionsDifference[2] / size[2] : 0;
	projectionsDifference[0] -= type[0] == borderType::periodic ?
		size[0] * (((__int64)(2 * d[0])) - (__int64)d[0])
		: 0;
	projectionsDifference[1] -= type[1] == borderType::periodic ?
		size[1] * (((__int64)(2 * d[1])) - (__int64)d[1])
		: 0;
	projectionsDifference[2] -= type[2] == borderType::periodic ?
		size[2] * (((__int64)(2 * d[2])) - (__int64)d[2])
		: 0;
	squaredDistance +=	projectionsDifference[0] * projectionsDifference[0] + 
						projectionsDifference[1] * projectionsDifference[1] + 
						projectionsDifference[2] * projectionsDifference[2];
#elif DIMENSIONAL_NUMBER == 2
	double d[2];
	d[0] = type[0] == borderType::periodic ? projectionsDifference[0] / size[0] : 0;
	d[1] = type[1] == borderType::periodic ? projectionsDifference[1] / size[1] : 0;
	projectionsDifference[0] -= type[0] == borderType::periodic ?
		size[0] * (((__int64)(2 * d[0])) - (__int64)d[0])
		: 0;
	projectionsDifference[1] -= type[1] == borderType::periodic ?
		size[1] * (((__int64)(2 * d[1])) - (__int64)d[1])
		: 0;
	squaredDistance +=	projectionsDifference[0] * projectionsDifference[0] + 
						projectionsDifference[1] * projectionsDifference[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		if (type[i] == borderType::periodic)
		{
			projectionsDifference[i] -= size[i] * (
				((__int64)(2 * projectionsDifference[i] / size[i])) -
				(__int64)(projectionsDifference[i] / size[i])
				);
		}
		squaredDistance += projectionsDifference[i] * projectionsDifference[i];
	}
#endif
	return sqrt(squaredDistance);
}
