#include "Vector.h"

Vector::Vector() noexcept: projections{}
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

Vector::VectorPass Vector::operator = (ConstVectorPass other) noexcept
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

Vector Vector::operator + (ConstVectorPass other) const noexcept
{
	Vector result = *this;
	result += other;
	return result;
}

Vector Vector::operator - (ConstVectorPass other) const noexcept
{
	Vector result = *this;
	result -= other;
	return result;
}

Vector::VectorPass Vector::operator += (ConstVectorPass other) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] += other.projections[i];
	}
	return *this;
}

Vector::VectorPass Vector::operator -= (ConstVectorPass other) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] -= other.projections[i];
	}
	return *this;
}

Vector::VectorPass Vector::operator *= (const double factor) noexcept
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] *= factor;
	}
	return *this;
}

Vector::VectorPass Vector::operator /= (const double divider)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] /= divider;
	}
	return *this;
}

const Vector operator * (Vector::ConstVectorPass vector, const double factor) noexcept
{
	Vector result = vector;
	result *= factor;
	return result;
}

const Vector operator * (const double factor, Vector::ConstVectorPass vector) noexcept
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
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result += projections[i] * projections[i];
	}
	return result;
}

double Vector::absoluteValue() const noexcept
{
	return sqrt(sumSquares());
}
