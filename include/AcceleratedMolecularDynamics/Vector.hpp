#pragma once
#ifndef TAHD_PROJECTION_TUPLE_H
#define TAHD_PROJECTION_TUPLE_H

#include "constants/constants.hpp"
#include <initializer_list>

namespace md
{
	/* Replying for working with vector quantities. 
	Also used to store the spatial sizes of objects of such classes as the system, cell, etc. */
	class Vector
	{
	private:
		std::array<double, kDimensionalNumber> projections;

	public:
		//this is type of index for this->projections array
		using projection_index = std::remove_const_t<decltype(kDimensionalNumber)>;	
		using iterator = decltype(projections)::iterator;
		using const_iterator = decltype(projections)::const_iterator;
		/* ConstPass is type for pass to fonctions and return from functions by value or reference 
		depending on the kDimensionalNumber and kMaxDimensionalForValuePassing. */
		using ConstPass = PassConstT<double, Vector>;

		Vector() noexcept;
		Vector(PassConstArrayT<double> projectionArray) noexcept;
		Vector(const double projectionArray[kDimensionalNumber]) noexcept;
		Vector(const std::initializer_list<double>& init_list);
		Vector(const Vector& other) noexcept;

		Vector& operator = (ConstPass other) noexcept;
		Vector operator - () const noexcept;
		Vector& operator += (ConstPass other) noexcept;
		Vector& operator -= (ConstPass other) noexcept;
		Vector& operator *= (double factor) noexcept;
		Vector& operator /= (double divider);
		double& operator [] (projection_index index);
		double operator [] (projection_index index) const;

		double sumSquares() const noexcept;				//sum of squares of elements
		double absoluteValue() const noexcept;			//square root of squares of elements sum

		projection_index size() const noexcept;

		iterator begin() noexcept;
		iterator end() noexcept;
		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;
		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;
	};

	Vector operator + (Vector::ConstPass first, Vector::ConstPass second) noexcept;
	Vector operator - (Vector::ConstPass first, Vector::ConstPass second) noexcept;
	Vector operator * (Vector::ConstPass vector, double factor) noexcept;
	Vector operator * (double factor, Vector::ConstPass vector) noexcept;
	Vector operator / (Vector::ConstPass vector, double divider);
}

#endif	//TAHD_PROJECTION_TUPLE_H
