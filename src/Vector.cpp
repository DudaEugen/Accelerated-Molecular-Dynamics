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
	auto begin = init_list.begin();
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] = init_list.size() > i ? *(begin + i) : 0;
	}
}

md::Vector::Vector(const Vector& other) noexcept
{
	for (projection_index i = 0; i < kDimensionalNumber; ++i)
	{
		projections[i] = other.projections[i];
	}
}

md::Vector::projection_index md::Vector::size() const noexcept
{
	return kDimensionalNumber;
}

double* md::Vector::data() noexcept
{
	return projections.data();
}

const double* md::Vector::data() const noexcept
{
	return projections.data();
}

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
	return *this * (-1);
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
	return *this += -other;
}

md::Vector& md::Vector::operator *= (double factor) noexcept
{
	for (double& projection: projections)
	{
		projection *= factor;
	}
	return *this;
}

md::Vector& md::Vector::operator /= (double divider)
{
	return *this *= 1/divider;
}

md::Vector md::operator + (Vector::ConstPass first, Vector::ConstPass second) noexcept
{
	Vector result = first;
	result += second;
	return result;
}

md::Vector md::operator - (Vector::ConstPass first, Vector::ConstPass second) noexcept
{
	Vector result = first;
	result -= second;
	return result;
}

md::Vector md::operator * (Vector::ConstPass vector, double factor) noexcept
{
	Vector result = vector;
	result *= factor;
	return result;
}

md::Vector md::operator * (double factor, Vector::ConstPass vector) noexcept
{
	return vector * factor;
}

md::Vector md::operator / (Vector::ConstPass vector, double divider)
{
	Vector result = vector;
	result /= divider;
	return result;
}

double& md::Vector::operator [] (projection_index index)
{
	return projections[index];
}

double md::Vector::operator [] (projection_index index) const
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
	return std::sqrt(sumSquares());
}

md::Vector::iterator md::Vector::begin() noexcept
{
	return projections.begin();
}

md::Vector::iterator md::Vector::end() noexcept
{
	return projections.end();
}

md::Vector::const_iterator md::Vector::begin() const noexcept
{
	return projections.begin();
}

md::Vector::const_iterator md::Vector::end() const noexcept
{
	return projections.end();
}

md::Vector::const_iterator md::Vector::cbegin() const noexcept
{
	return projections.cbegin();
}

md::Vector::const_iterator md::Vector::cend() const noexcept
{
	return projections.cend();
}
