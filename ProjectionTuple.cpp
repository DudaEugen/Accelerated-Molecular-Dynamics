#include "ProjectionTuple.h"

ProjectionTuple::ProjectionTuple(): projections{}
{
}

ProjectionTuple::ProjectionTuple(const double projectionArray[DIMENSIONAL_NUMBER]): projections{}
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

ProjectionTuple::ProjectionTuple(const ProjectionTuple& projectionTuple): projections{}
{
#if DIMENSIONAL_NUMBER == 3
	projections[0] = projectionTuple.projections[0];
	projections[1] = projectionTuple.projections[1];
	projections[2] = projectionTuple.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	projections[0] = projectionTuple.projections[0];
	projections[1] = projectionTuple.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionTuple.projections[i];
	}
#endif
}

void ProjectionTuple::operator = (const ProjectionTuple &other)
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
}

ProjectionTuple ProjectionTuple::operator + (const ProjectionTuple &other) const
{
	ProjectionTuple result = ProjectionTuple();
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] = projections[0] + other.projections[0];
	result.projections[1] = projections[1] + other.projections[1];
	result.projections[2] = projections[2] + other.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] = projections[0] + other.projections[0];
	result.projections[1] = projections[1] + other.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] + other.projections[i];
	}
#endif
	return result;
}

ProjectionTuple ProjectionTuple::operator - (const ProjectionTuple &other) const
{
	ProjectionTuple result = ProjectionTuple();
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] = projections[0] - other.projections[0];
	result.projections[1] = projections[1] - other.projections[1];
	result.projections[2] = projections[2] - other.projections[2];
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] = projections[0] - other.projections[0];
	result.projections[1] = projections[1] - other.projections[1];
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] - other.projections[i];
	}
#endif
	return result;
}

void ProjectionTuple::operator += (const ProjectionTuple &other)
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
}

void ProjectionTuple::operator -= (const ProjectionTuple &other)
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
}

void ProjectionTuple::operator *= (const double factor)
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
}

void ProjectionTuple::operator /= (const double divider)
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
}

const ProjectionTuple operator * (const ProjectionTuple &projectionTuple, const double factor)
{
	ProjectionTuple result = ProjectionTuple();
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] = projectionTuple.projections[0] * factor;
	result.projections[1] = projectionTuple.projections[1] * factor;
	result.projections[2] = projectionTuple.projections[2] * factor;
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] = projectionTuple.projections[0] * factor;
	result.projections[1] = projectionTuple.projections[1] * factor;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projectionTuple.projections[i] * factor;
	}
#endif
	return result;
}

const ProjectionTuple operator * (const double factor, const ProjectionTuple &projectionTuple) 
{
	ProjectionTuple result = ProjectionTuple();
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] = projectionTuple.projections[0] * factor;
	result.projections[1] = projectionTuple.projections[1] * factor;
	result.projections[2] = projectionTuple.projections[2] * factor;
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] = projectionTuple.projections[0] * factor;
	result.projections[1] = projectionTuple.projections[1] * factor;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projectionTuple.projections[i] * factor;
	}
#endif
	return result;
}

ProjectionTuple ProjectionTuple::operator / (const double divider) const
{
	ProjectionTuple result = ProjectionTuple();
#if DIMENSIONAL_NUMBER == 3
	result.projections[0] = projections[0] / divider;
	result.projections[1] = projections[1] / divider;
	result.projections[2] = projections[2] / divider;
#elif DIMENSIONAL_NUMBER == 2
	result.projections[0] = projections[0] / divider;
	result.projections[1] = projections[1] / divider;
#else
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] / divider;
	}
#endif
	return result;
}

double& ProjectionTuple::operator [] (const projection_index index)
{
	return projections[index];
}

double ProjectionTuple::operator [] (const projection_index index) const
{
	return projections[index];
}

double ProjectionTuple::sumSquares() const
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

double ProjectionTuple::absoluteValue() const
{
	return sqrt(sumSquares());
}
