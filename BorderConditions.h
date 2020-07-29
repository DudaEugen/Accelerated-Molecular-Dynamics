#pragma once
#ifndef TAHD_BORDER_CONDITIONS_H
#define TAHD_BORDER_CONDITIONS_H

#include <cstdint>
#include "Vector.h"

/* Borders are surfeces, that have i-th coordionate x[i] such that x[i] == 0 or x[i] == size[i]
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
public:
	BorderConditions(Vector::ConstVectorPass size, borderType borders[DIMENSIONAL_NUMBER]) noexcept;
	double operator() (Vector& projectionsDifference) const noexcept;
};

#endif	//TAHD_BORDER_CONDITIONS_H
