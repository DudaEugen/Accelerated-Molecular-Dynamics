#pragma once
#ifndef TAHD_BORDER_CONDITIONS_H
#define TAHD_BORDER_CONDITIONS_H

#include <cstdint>
#include "Vector.hpp"

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
	borderType type[DIMENSIONAL_NUMBER];
	Vector size;
	Vector zeroPoint;
public:
	BorderConditions(Vector::ConstVectorPass size, borderType borders[DIMENSIONAL_NUMBER]) noexcept;
	BorderConditions(Vector::ConstVectorPass size, borderType borders[DIMENSIONAL_NUMBER],
					 Vector::ConstVectorPass zeroPoint) noexcept;
	const borderType* getBorderTypes() const noexcept;
	Vector::ConstVectorPass getSize() const noexcept;
	Vector::ConstVectorPass getZeroPoint() const noexcept;
	// compute position considering border conditions
	Vector computePosition(Vector::ConstVectorPass coordinates) const;
	double operator() (Vector& projectionsDifference) const;
};

#endif	//TAHD_BORDER_CONDITIONS_H
