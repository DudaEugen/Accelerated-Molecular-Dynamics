#include "BorderConditions.hpp"
#include <cmath>
#include <cstdint>
#include "utility/Zip.hpp"

BorderConditions::BorderConditions(Vector::ConstVectorPass size, const std::array<borderType, DIMENSIONAL_NUMBER> borders) noexcept
	: dimensions{ size }
{
	for (auto [type, border]: Zip(borderTypes, borders))
		type = border;
}

BorderConditions::BorderConditions(Vector::ConstVectorPass size, const std::array<borderType, DIMENSIONAL_NUMBER> borders,
					 			  Vector::ConstVectorPass zeroPoint) noexcept
	: BorderConditions{ size, borders }
{
	this->zeroPoint = zeroPoint;
}

const BorderConditions::borderType* BorderConditions::getBorderTypes() const noexcept { return borderTypes.data(); }

Vector::ConstVectorPass BorderConditions::getSize() const noexcept { return dimensions; }

Vector::ConstVectorPass BorderConditions::getZeroPoint() const noexcept { return zeroPoint; }

Vector BorderConditions::computePosition(Vector::ConstVectorPass coordinates) const
{
	Vector result;
	for (auto [res, coordinate, type, size, zPoint]: Zip(result, coordinates, borderTypes, dimensions, zeroPoint))
	{
		res = coordinate;
		if (type == borderType::periodic)
			res -= size * static_cast<int64_t>(std::floor((res - zPoint) / size));
	}
	return result;
}

double BorderConditions::operator() (Vector& projectionsDifference) const
{
	double squaredDistance = 0;
	double ratioProjToSize;
	for (auto [type, projectionDifference, size]: Zip(borderTypes, projectionsDifference, dimensions))
	{
		if (type == borderType::periodic)
		{
			ratioProjToSize = projectionDifference / size;
			projectionDifference -= size * (
				static_cast<int64_t>(2 * ratioProjToSize) -
				static_cast<int64_t>(ratioProjToSize)
			);
		}
		squaredDistance += projectionDifference * projectionDifference;
	}
	return sqrt(squaredDistance);
}
