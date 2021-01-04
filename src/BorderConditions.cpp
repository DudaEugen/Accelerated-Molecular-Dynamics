#include "BorderConditions.hpp"
#include <cmath>
#include <cstdint>
#include "Zip.hpp"

BorderConditions::BorderConditions(Vector::ConstPass size, ConstPassArrayT<borderType> borders) noexcept
	: dimensions{ size }
{
	for (auto [type, border]: utils::zip::Zip(borderTypes, borders))
		type = border;
}

BorderConditions::BorderConditions(Vector::ConstPass size, ConstPassArrayT<borderType> borders,
					 			  Vector::ConstPass zeroPoint) noexcept
	: BorderConditions{ size, borders }
{
	this->zeroPoint = zeroPoint;
}

const BorderConditions::borderType* BorderConditions::getBorderTypes() const noexcept { return borderTypes.data(); }

Vector::ConstPass BorderConditions::getSize() const noexcept { return dimensions; }

Vector::ConstPass BorderConditions::getZeroPoint() const noexcept { return zeroPoint; }

Vector BorderConditions::computePosition(Vector::ConstPass coordinates) const
{
	Vector result;
	for (auto [res, coordinate, type, size, zPoint]: 
		 utils::zip::Zip(result, coordinates, borderTypes, dimensions, zeroPoint))
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
	for (auto [type, projectionDifference, size]: utils::zip::Zip(borderTypes, projectionsDifference, dimensions))
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
