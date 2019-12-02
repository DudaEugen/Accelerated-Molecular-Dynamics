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
	ProjectionTuple(const ProjectionTuple &projectionTuple);
	void operator = (const ProjectionTuple &other);
	ProjectionTuple operator + (const ProjectionTuple &other) const;
	ProjectionTuple operator - (const ProjectionTuple &other) const;
	void operator += (const ProjectionTuple &other);
	void operator -= (const ProjectionTuple &other);
	void operator *= (const double factor);
	void operator /= (const double divider);
	ProjectionTuple operator / (const double divider) const;
	friend const ProjectionTuple operator * (const ProjectionTuple &projectionTuple, const double factor);
	friend const ProjectionTuple operator * (const double factor, const ProjectionTuple &projectionTuple);
};

#endif	//TAHD_PROJECTION_TUPLE_H

