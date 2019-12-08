#include "ProjectionTuple.h"

ProjectionTuple::ProjectionTuple(): projections{}
{
}

ProjectionTuple::ProjectionTuple(const double projectionArray[DIMENSIONAL_NUMBER]): projections{}
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionArray[i];
	}
}

ProjectionTuple::ProjectionTuple(const ProjectionTuple& projectionTuple): projections{}
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionTuple.projections[i];
	}
}

void ProjectionTuple::operator = (const ProjectionTuple &other)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = other.projections[i];
	}
}

ProjectionTuple ProjectionTuple::operator + (const ProjectionTuple &other) const
{
	ProjectionTuple result = ProjectionTuple();
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] + other.projections[i];
	}
	return result;
}

ProjectionTuple ProjectionTuple::operator - (const ProjectionTuple &other) const
{
	ProjectionTuple result = ProjectionTuple();
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] - other.projections[i];
	}
	return result;
}

void ProjectionTuple::operator += (const ProjectionTuple &other)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] += other.projections[i];
	}
}

void ProjectionTuple::operator -= (const ProjectionTuple &other)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] -= other.projections[i];
	}
}

void ProjectionTuple::operator *= (const double factor)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] *= factor;
	}
}

void ProjectionTuple::operator /= (const double divider)
{
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] /= divider;
	}
}

const ProjectionTuple operator * (const ProjectionTuple &projectionTuple, const double factor)
{
	ProjectionTuple result = ProjectionTuple();
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projectionTuple.projections[i] * factor;
	}
	return result;
}

const ProjectionTuple operator * (const double factor, const ProjectionTuple &projectionTuple) 
{
	return projectionTuple * factor;
}

ProjectionTuple ProjectionTuple::operator / (const double divider) const
{
	ProjectionTuple result = ProjectionTuple();
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] / divider;
	}
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
	for (projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result += projections[i] * projections[i];
	}
	return result;
}

double ProjectionTuple::absoluteValue() const
{
	return sqrt(sumSquares());
}
