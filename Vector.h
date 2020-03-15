#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants.h"
#include <initializer_list>

typedef unsigned short int projection_index;		//this is type of index for this->projections array

/*this class replying for working with vector quantities 
this class is also used to store the spatial sizes of objects of such classes as the system, cell, etc.*/
class Vector
{
private:
	double projections[DIMENSIONAL_NUMBER];
public:
	/* VectorPass is type for pass to fonctions and return from functions by value or reference 
	depending on the DIMENSIONAL_NUMBER and MAX_DIMENSIONAL_FOR_VALUE_PASSING */
	#if DIMENSIONAL_NUMBER > MAX_DIMENSIONAL_FOR_VALUE_PASSING
		typedef Vector& VectorPass;
		typedef const Vector& ConstVectorPass;
	#else
		typedef Vector VectorPass;
		typedef const Vector ConstVectorPass;
	#endif

	Vector();
	Vector(const double projectionArray[DIMENSIONAL_NUMBER]);
	Vector(const std::initializer_list<double>& init_list);
	Vector(const Vector& vector);
	VectorPass operator = (ConstVectorPass other);
	Vector operator - () const;
	Vector operator + (ConstVectorPass other) const;
	Vector operator - (ConstVectorPass other) const;
	VectorPass operator += (ConstVectorPass other);
	VectorPass operator -= (ConstVectorPass other);
	VectorPass operator *= (const double factor);
	VectorPass operator /= (const double divider);
	double& operator [] (const projection_index index);
	double operator [] (const projection_index index) const;
	Vector operator / (const double divider) const;
	friend const Vector operator * (ConstVectorPass vector, const double factor);
	friend const Vector operator * (const double factor, ConstVectorPass vector);
	double sumSquares() const;				//sum of squares of elements
	double absoluteValue() const;			//square root of squares of elements sum
};

#endif	//TAHD_PROJECTION_TUPLE_H

