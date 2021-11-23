#include "Vector.hpp"
#include <cmath>

md::Vector::Vector() noexcept: projections{}
{
}

md::Vector::Vector(PassConstArrayT<double> projectionArray) noexcept
	: projections{ projectionArray }
{
}

md::Vector::Vector(const double projectionArray[kDimensionalNumber]) noexcept
{
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] = projectionArray[i];
	}
}

md::Vector::Vector(const std::initializer_list<double>& init_list)
{
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] = init_list.size() > i ? *(init_list.begin() + i) : 0;
	}
}

md::Vector::Vector(const Vector& Vector) noexcept
{
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] = Vector.projections[i];
	}
}

md::Vector::projection_index md::Vector::size() const noexcept { return kDimensionalNumber; }

md::Vector& md::Vector::operator = (ConstPass other) noexcept
{
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] = other.projections[i];
	}
	return *this;
}

md::Vector md::Vector::operator - () const noexcept
{
	Vector result;
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		result.projections[i] = -projections[i];
	}
	return result;
}

md::Vector md::Vector::operator + (ConstPass other) const noexcept
{
	Vector result = *this;
	result += other;
	return result;
}

md::Vector md::Vector::operator - (ConstPass other) const noexcept
{
	Vector result = *this;
	result -= other;
	return result;
}

md::Vector& md::Vector::operator += (ConstPass other) noexcept
{
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] += other.projections[i];
	}
	return *this;
}

md::Vector& md::Vector::operator -= (ConstPass other) noexcept
{
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] -= other.projections[i];
	}
	return *this;
}

md::Vector& md::Vector::operator *= (const double factor) noexcept
{
	for (double& projection: projections)
	{
		projection *= factor;
	}
	return *this;
}

md::Vector& md::Vector::operator /= (const double divider)
{
	for (double& projection: projections)
	{
		projection /= divider;
	}
	return *this;
}

const md::Vector md::operator * (Vector::ConstPass vector, const double factor) noexcept
{
	Vector result = vector;
	result *= factor;
	return result;
}

const md::Vector md::operator * (const double factor, Vector::ConstPass vector) noexcept
{
	Vector result = vector;
	result *= factor;
	return result;
}

md::Vector md::Vector::operator / (const double divider) const
{
	Vector result = *this;
	result /= divider;
	return result;
}

double& md::Vector::operator [] (const projection_index index)
{
	return projections[index];
}

double md::Vector::operator [] (const projection_index index) const
{
	return projections[index];
}

double md::Vector::sumSquares() const noexcept
{
	double result = 0;
	for (double projection: projections)
	{
		result += projection * projection;
	}
	return result;
}

double md::Vector::absoluteValue() const noexcept
{
	return sqrt(sumSquares());
}

md::Vector::iterator md::Vector::begin() noexcept { return projections.begin(); }

md::Vector::iterator md::Vector::end() noexcept { return projections.end(); }

md::Vector::const_iterator md::Vector::begin() const noexcept { return projections.begin(); }

md::Vector::const_iterator md::Vector::end() const noexcept { return projections.end(); }
