#include "Vector.hpp"
#include <cmath>

Vector::Vector() noexcept: projections{}
{
}

Vector::Vector(ConstPassArrayT<double> projectionArray) noexcept
	: projections{ projectionArray }
{
}

Vector::Vector(const double projectionArray[DIMENSIONAL_NUMBER]) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionArray[i];
	}
}

Vector::Vector(const std::initializer_list<double>& init_list)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = init_list.size() > i ? *(init_list.begin() + i) : 0;
	}
}

Vector::Vector(const Vector& Vector) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = Vector.projections[i];
	}
}

Vector::projection_index Vector::size() const noexcept { return DIMENSIONAL_NUMBER; }

Vector::Pass Vector::operator = (ConstPass other) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = other.projections[i];
	}
	return *this;
}

Vector Vector::operator - () const noexcept
{
	Vector result;
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = -projections[i];
	}
	return result;
}

Vector Vector::operator + (ConstPass other) const noexcept
{
	Vector result = *this;
	result += other;
	return result;
}

Vector Vector::operator - (ConstPass other) const noexcept
{
	Vector result = *this;
	result -= other;
	return result;
}

Vector::Pass Vector::operator += (ConstPass other) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] += other.projections[i];
	}
	return *this;
}

Vector::Pass Vector::operator -= (ConstPass other) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] -= other.projections[i];
	}
	return *this;
}

Vector::Pass Vector::operator *= (const double factor) noexcept
{
	for (double& projection: projections)
	{
		projection *= factor;
	}
	return *this;
}

Vector::Pass Vector::operator /= (const double divider)
{
	for (double& projection: projections)
	{
		projection /= divider;
	}
	return *this;
}

const Vector operator * (Vector::ConstPass vector, const double factor) noexcept
{
	Vector result = vector;
	result *= factor;
	return result;
}

const Vector operator * (const double factor, Vector::ConstPass vector) noexcept
{
	Vector result = vector;
	result *= factor;
	return result;
}

Vector Vector::operator / (const double divider) const
{
	Vector result = *this;
	result /= divider;
	return result;
}

double& Vector::operator [] (const projection_index index)
{
	return projections[index];
}

double Vector::operator [] (const projection_index index) const
{
	return projections[index];
}

double Vector::sumSquares() const noexcept
{
	double result = 0;
	for (double projection: projections)
	{
		result += projection * projection;
	}
	return result;
}

double Vector::absoluteValue() const noexcept
{
	return sqrt(sumSquares());
}

Vector::iterator Vector::begin() noexcept { return projections.begin(); }

Vector::iterator Vector::end() noexcept { return projections.end(); }

Vector::const_iterator Vector::begin() const noexcept { return projections.begin(); }

Vector::const_iterator Vector::end() const noexcept { return projections.end(); }
