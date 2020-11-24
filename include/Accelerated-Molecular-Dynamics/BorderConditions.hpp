#pragma once
#ifndef TAHD_BORDER_CONDITIONS_H
#define TAHD_BORDER_CONDITIONS_H

#include "Vector.hpp"
#include <array>

/* Borders are surfeces, that have i-th coordionate x[i] 
such that x[i] == zeroPoint[i] or x[i] == zeroPoint[i] + size[i] (default all zeroPoint coordinates = 0)
BorderConditions object recalculating istances between atoms
This class is realizing periodic borders and "none" borders (if border not defined in this direction)  */
class BorderConditions
{
public:
	enum class borderType {
		periodic,
		none,
	};
private:
	std::array<borderType, DIMENSIONAL_NUMBER> borderTypes;
	Vector dimensions;
	Vector zeroPoint;
public:
	BorderConditions(Vector::ConstVectorPass size, const std::array<borderType, DIMENSIONAL_NUMBER> borders) noexcept;
	BorderConditions(Vector::ConstVectorPass size, const std::array<borderType, DIMENSIONAL_NUMBER> borders,
					 Vector::ConstVectorPass zeroPoint) noexcept;
	const borderType* getBorderTypes() const noexcept;
	Vector::ConstVectorPass getSize() const noexcept;
	Vector::ConstVectorPass getZeroPoint() const noexcept;
	// compute position considering border conditions
	Vector computePosition(Vector::ConstVectorPass coordinates) const;
	double operator() (Vector& projectionsDifference) const;
};

#endif	//TAHD_BORDER_CONDITIONS_H
