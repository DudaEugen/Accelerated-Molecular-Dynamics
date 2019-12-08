#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants.h"

typedef unsigned short int projection_index;		//this is type of index for this->projections array

/*this class replying for working with vector quantities 
name "Vector" is not used  to avoid confusions with std::vector and facilitate reading code this way
this class is also used to store the spatial sizes of objects of such classes as the system, cell, etc.*/
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
	double& operator [] (const projection_index index);
	double operator [] (const projection_index index) const;
	ProjectionTuple operator / (const double divider) const;
	friend const ProjectionTuple operator * (const ProjectionTuple &projectionTuple, const double factor);
	friend const ProjectionTuple operator * (const double factor, const ProjectionTuple &projectionTuple);
	double sumSquares() const;				//sum of squares of elements
	double absoluteValue() const;			//square root of squares of elements sum
};

#endif	//TAHD_PROJECTION_TUPLE_H

