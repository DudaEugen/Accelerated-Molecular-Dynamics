#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants.h"

//this class replying for working with vector quantities 
//name "Vector" is not used  to avoid confusions with std::vector and facilitate reading code this way
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
	void convertToArray(double array[DIMENSIONAL_NUMBER]) const;
};

#endif	//TAHD_PROJECTION_TUPLE_H

