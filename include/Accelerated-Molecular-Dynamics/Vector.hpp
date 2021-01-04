#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants.hpp"
#include <initializer_list>

namespace md
{
	/*this class replying for working with vector quantities 
	this class is also used to store the spatial sizes of objects of such classes as the system, cell, etc.*/
	class Vector
	{
	private:
		using element_t = double;

		std::array<element_t, DIMENSIONAL_NUMBER> projections;
	public:
		//this is type of index for this->projections array
		using projection_index = std::remove_const_t<decltype(DIMENSIONAL_NUMBER)>;	
		using iterator = decltype(projections)::iterator;
		using const_iterator = decltype(projections)::const_iterator;
		/* Pass and ConstPass is type for pass to fonctions and return from functions by value or reference 
		depending on the DIMENSIONAL_NUMBER and MAX_DIMENSIONAL_FOR_VALUE_PASSING.
		Don't use Pass for change Vector in function (pass Vector& or Vector* to function for this) */
		using Pass = PassT<element_t, Vector>;
		using ConstPass = PassT<element_t, const Vector>;

		Vector() noexcept;
		Vector(ConstPassArrayT<double> projectionArray) noexcept;
		Vector(const double projectionArray[DIMENSIONAL_NUMBER]) noexcept;
		Vector(const std::initializer_list<double>& init_list);
		Vector(const Vector& vector) noexcept;
		projection_index size() const noexcept;
		Pass operator = (ConstPass other) noexcept;
		Vector operator - () const noexcept;
		Vector operator + (ConstPass other) const noexcept;
		Vector operator - (ConstPass other) const noexcept;
		Pass operator += (ConstPass other) noexcept;
		Pass operator -= (ConstPass other) noexcept;
		Pass operator *= (const double factor) noexcept;
		Pass operator /= (const double divider);
		double& operator [] (const projection_index index);
		double operator [] (const projection_index index) const;
		Vector operator / (const double divider) const;
		double sumSquares() const noexcept;				//sum of squares of elements
		double absoluteValue() const noexcept;			//square root of squares of elements sum

		iterator begin() noexcept;
		iterator end() noexcept;
		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;
	};

	const Vector operator * (Vector::ConstPass vector, const double factor) noexcept;
	const Vector operator * (const double factor, Vector::ConstPass vector) noexcept;
}

#endif	//TAHD_PROJECTION_TUPLE_H
