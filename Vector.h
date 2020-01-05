#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants.h"

typedef unsigned short int projection_index;		//this is type of index for this->projections array

/*this class replying for working with vector quantities 
this class is also used to store the spatial sizes of objects of such classes as the system, cell, etc.*/
class Vector
{
private:
	double projections[DIMENSIONAL_NUMBER];
public:
	Vector();
	Vector(const double projectionArray[DIMENSIONAL_NUMBER]);
	Vector(const Vector &vector);
	void operator = (const Vector other);
	Vector operator + (const Vector other) const;
	Vector operator - (const Vector other) const;
	void operator += (const Vector other);
	void operator -= (const Vector other);
	void operator *= (const double factor);
	void operator /= (const double divider);
	double& operator [] (const projection_index index);
	double operator [] (const projection_index index) const;
	Vector operator / (const double divider) const;
	friend const Vector operator * (const Vector vector, const double factor);
	friend const Vector operator * (const double factor, const Vector vector);
	double sumSquares() const;				//sum of squares of elements
	double absoluteValue() const;			//square root of squares of elements sum
};

#endif	//TAHD_PROJECTION_TUPLE_H

