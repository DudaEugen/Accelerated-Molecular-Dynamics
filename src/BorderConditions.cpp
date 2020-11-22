#include "BorderConditions.hpp"

BorderConditions::BorderConditions(Vector::ConstVectorPass size, borderType borders[DIMENSIONAL_NUMBER]) noexcept
	: size{ size }
{
	for (Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		type[i] = borders[i];
}

BorderConditions::BorderConditions(Vector::ConstVectorPass size, borderType borders[DIMENSIONAL_NUMBER],
					 			  Vector::ConstVectorPass zeroPoint) noexcept
	: BorderConditions{ size, borders }
{
	this->zeroPoint = zeroPoint;
}

const BorderConditions::borderType* BorderConditions::getBorderTypes() const noexcept { return type; }

Vector::ConstVectorPass BorderConditions::getSize() const noexcept { return size; }

Vector::ConstVectorPass BorderConditions::getZeroPoint() const noexcept { return zeroPoint; }

Vector BorderConditions::computePosition(Vector::ConstVectorPass coordinates) const
{
	Vector result;
	for(Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result[i] = coordinates[i];
		if (type[i] == borderType::periodic)
				result[i] -= size[i] * static_cast<int64_t>(std::floor(
												(result[i] - zeroPoint[i]) / size[i]));
	}
	return result;
}

double BorderConditions::operator() (Vector& projectionsDifference) const
{
	double squaredDistance = 0;
	double ratioProjToSize;
	for (Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
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
