#include "Vector.h"

Vector::Vector(): projections{}
{
}

Vector::Vector(const double projectionArray[DIMENSIONAL_NUMBER]): projections{}
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] = projectionArray[0];
	projections[1] = projectionArray[1];
	projections[2] = projectionArray[2];
#elif DIMENSIONAL_NUMBER == 2
	projections[0] = projectionArray[0];
	projections[1] = projectionArray[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionArray[i];
	}
#endif
}

Vector::Vector(const std::initializer_list<double>& init_list)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = init_list.size() > i ? *(init_list.begin() + i) : 0;
	}
}

Vector::Vector(const Vector& Vector): projections{}
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] = Vector.projections[0];
	projections[1] = Vector.projections[1];
	projections[2] = Vector.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	projections[0] = Vector.projections[0];
	projections[1] = Vector.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = Vector.projections[i];
	}
#endif
}

Vector Vector::operator = (const Vector other)
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] = other.projections[0];
	projections[1] = other.projections[1];
	projections[2] = other.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	projections[0] = other.projections[0];
	projections[1] = other.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = other.projections[i];
	}
#endif
	return *this;
}

Vector Vector::operator - () const
{
	Vector result;
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] = -projections[0];
	result.projections[1] = -projections[1];
	result.projections[2] = -projections[2];
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] = -projections[0];
	result.projections[1] = -projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = -projections[i];
	}
#endif
	return result;
}

Vector Vector::operator + (const Vector other) const
{
	Vector result = *this;
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] += other.projections[0];
	result.projections[1] += other.projections[1];
	result.projections[2] += other.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] += other.projections[0];
	result.projections[1] += other.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] += other.projections[i];
	}
#endif
	return result;
}

Vector Vector::operator - (const Vector other) const
{
	Vector result = *this;
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] -= other.projections[0];
	result.projections[1] -= other.projections[1];
	result.projections[2] -= other.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] -= other.projections[0];
	result.projections[1] -= other.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] -= other.projections[i];
	}
#endif
	return result;
}

Vector& Vector::operator += (const Vector other)
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] += other.projections[0];
	projections[1] += other.projections[1];
	projections[2] += other.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	projections[0] += other.projections[0];
	projections[1] += other.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] += other.projections[i];
	}
#endif
	return *this;
}

Vector& Vector::operator -= (const Vector other)
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] -= other.projections[0];
	projections[1] -= other.projections[1];
	projections[2] -= other.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	projections[0] -= other.projections[0];
	projections[1] -= other.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] -= other.projections[i];
	}
#endif
	return *this;
}

Vector& Vector::operator *= (const double factor)
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] *= factor;
	projections[1] *= factor;
	projections[2] *= factor;
#elif DIMENSIONAL_NUMBER == 2
	projections[0] *= factor;
	projections[1] *= factor;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] *= factor;
	}
#endif
	return *this;
}

Vector& Vector::operator /= (const double divider)
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] /= divider;
	projections[1] /= divider;
	projections[2] /= divider;
#elif DIMENSIONAL_NUMBER == 2
	projections[0] /= divider;
	projections[1] /= divider;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] /= divider;
	}
#endif
	return *this;
}

const Vector operator * (const Vector vector, const double factor)
{
	Vector result = vector;
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] *= factor;
	result.projections[1] *= factor;
	result.projections[2] *= factor;
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] *= factor;
	result.projections[1] *= factor;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] *= factor;
	}
#endif
	return result;
}

const Vector operator * (const double factor, const Vector vector) 
{
	Vector result = vector;
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] *= factor;
	result.projections[1] *= factor;
	result.projections[2] *= factor;
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] *= factor;
	result.projections[1] *= factor;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] *= factor;
	}
#endif
	return result;
}

Vector Vector::operator / (const double divider) const
{
	Vector result = *this;
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] /= divider;
	result.projections[1] /= divider;
	result.projections[2] /= divider;
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] /= divider;
	result.projections[1] /= divider;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] /= divider;
	}
#endif
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

double Vector::sumSquares() const
{
	double result = 0;
#if DIMENSIONAL_NUMBER == 3
	result += projections[0] * projections[0] + projections[1] * projections[1] + projections[2] * projections[2];
#elif DIMENSIONAL_NUMBER == 2
	result += projections[0] * projections[0] + projections[1] * projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result += projections[i] * projections[i];
	}
#endif
	return result;
}

double Vector::absoluteValue() const
{
	return sqrt(sumSquares());
}
