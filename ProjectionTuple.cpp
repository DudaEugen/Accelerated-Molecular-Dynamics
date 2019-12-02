#include "ProjectionTuple.h"

typedef unsigned short int index;

ProjectionTuple::ProjectionTuple()
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = 0;
	}
}

ProjectionTuple::ProjectionTuple(const double projectionArray[DIMENSIONAL_NUMBER])
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionArray[i];
	}
}

ProjectionTuple::ProjectionTuple(const ProjectionTuple& projectionTuple)
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionTuple.projections[i];
	}
}

void ProjectionTuple::operator = (const ProjectionTuple &other)
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = other.projections[i];
	}
}

ProjectionTuple ProjectionTuple::operator + (const ProjectionTuple &other) const
{
	ProjectionTuple result = ProjectionTuple();
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] + other.projections[i];
	}
	return result;
}

ProjectionTuple ProjectionTuple::operator - (const ProjectionTuple &other) const
{
	ProjectionTuple result = ProjectionTuple();
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] - other.projections[i];
	}
	return result;
}

void ProjectionTuple::operator += (const ProjectionTuple &other)
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] += other.projections[i];
	}
}

void ProjectionTuple::operator -= (const ProjectionTuple &other)
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] -= other.projections[i];
	}
}

void ProjectionTuple::operator *= (const double factor)
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] *= factor;
	}
}

void ProjectionTuple::operator /= (const double divider)
{
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] /= divider;
	}
}

const ProjectionTuple operator * (const ProjectionTuple &projectionTuple, const double factor)
{
	ProjectionTuple result = ProjectionTuple();
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
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
	for (index i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		result.projections[i] = projections[i] / divider;
	}
	return result;
}
