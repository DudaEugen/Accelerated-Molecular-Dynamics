#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants.h"
#include <initializer_list>

/*this class replying for working with vector quantities 
this class is also used to store the spatial sizes of objects of such classes as the system, cell, etc.*/
class Vector
{
private:
	double projections[DIMENSIONAL_NUMBER];
public:
	using projection_index = unsigned char;		//this is type of index for this->projections array
	/* VectorPass is type for pass to fonctions and return from functions by value or reference 
	depending on the DIMENSIONAL_NUMBER and MAX_DIMENSIONAL_FOR_VALUE_PASSING */
	#if DIMENSIONAL_NUMBER > MAX_DIMENSIONAL_FOR_VALUE_PASSING
		using VectorPass = Vector&;
		using ConstVectorPass = const Vector&;
	#else
		using VectorPass = Vector;
		using ConstVectorPass = const Vector;
	#endif

	Vector() noexcept;
	Vector(const double projectionArray[DIMENSIONAL_NUMBER]) noexcept;
	Vector(const std::initializer_list<double>& init_list);
	Vector(const Vector& vector) noexcept;
	VectorPass operator = (ConstVectorPass other) noexcept;
	Vector operator - () const noexcept;
	Vector operator + (ConstVectorPass other) const noexcept;
	Vector operator - (ConstVectorPass other) const noexcept;
	VectorPass operator += (ConstVectorPass other) noexcept;
	VectorPass operator -= (ConstVectorPass other) noexcept;
	VectorPass operator *= (const double factor) noexcept;
	VectorPass operator /= (const double divider);
	double& operator [] (const projection_index index);
	double operator [] (const projection_index index) const;
	Vector operator / (const double divider) const;
	friend const Vector operator * (ConstVectorPass vector, const double factor) noexcept;
	friend const Vector operator * (const double factor, ConstVectorPass vector) noexcept;
	double sumSquares() const noexcept;				//sum of squares of elements
	double absoluteValue() const noexcept;			//square root of squares of elements sum

	class Iterator;
	class ConstIterator;

	Iterator begin() noexcept;
	Iterator end() noexcept;
	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;

	class Iterator
	{
	private:
		double* projection;

		Iterator(double* proj) noexcept;
	public:
		Iterator& operator++() noexcept;
		double& operator*() noexcept;
		bool operator!=(Iterator it) const noexcept;

		friend class Vector;
	};

	class ConstIterator
	{
	private:
		const double* projection;

		ConstIterator(const double* proj) noexcept;
	public:
		ConstIterator& operator++() noexcept;
		const double& operator*() const noexcept;
		bool operator!=(ConstIterator it) const noexcept;

		friend class Vector;
	};
};

#endif	//TAHD_PROJECTION_TUPLE_H
