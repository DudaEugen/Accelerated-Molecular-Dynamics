#include "ProjectionTuple.h"

ProjectionTuple::ProjectionTuple()
{
	for (unsigned short int i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = 0;
	}
}

ProjectionTuple::ProjectionTuple(const double projectionArray[DIMENSIONAL_NUMBER])
{
	for (unsigned short int i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionArray[i];
	}
}

ProjectionTuple::ProjectionTuple(const ProjectionTuple& projectionTuple)
{
	for (unsigned short int i = 0; i < DIMENSIONAL_NUMBER; ++i)
	{
		projections[i] = projectionTuple.projections[i];
	}
}
