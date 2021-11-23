#include "System/BorderConditions.hpp"
#include <cmath>
#include <cstdint>
#include "Zip.hpp"

md::BorderConditions::BorderConditions(Vector::ConstPass size, PassConstArrayT<borderType> borders) noexcept
	: dimensions{ size }
{
	for (auto [type, border]: utils::zip::Zip(borderTypes, borders))
		type = border;
}

md::BorderConditions::BorderConditions(Vector::ConstPass size, PassConstArrayT<borderType> borders,
					 			  Vector::ConstPass zeroPoint) noexcept
	: BorderConditions{ size, borders }
{
	this->zeroPoint = zeroPoint;
}

const md::BorderConditions::borderType* md::BorderConditions::getBorderTypes() const noexcept 
{ 
	return borderTypes.data(); 
}

md::Vector::ConstPass md::BorderConditions::getSize() const noexcept { return dimensions; }

md::Vector::ConstPass md::BorderConditions::getZeroPoint() const noexcept { return zeroPoint; }

md::Vector md::BorderConditions::computePosition(Vector::ConstPass coordinates) const
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

double md::BorderConditions::operator() (Vector& projectionsDifference) const
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
