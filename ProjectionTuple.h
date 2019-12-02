#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants.h"

class ProjectionTuple
{
private:
	double projections[DIMENSIONAL_NUMBER];
public:
	ProjectionTuple();
	ProjectionTuple(const double projectionArray[DIMENSIONAL_NUMBER]);
	ProjectionTuple(const ProjectionTuple& projectionTuple);
};

#endif	//TAHD_PROJECTION_TUPLE_H

