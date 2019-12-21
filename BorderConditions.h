#pragma once
#ifndef TAHD_BORDER_CONDITIONS_H
#define TAHD_BORDER_CONDITIONS_H

#include "ProjectionTuple.h"

/* Borders are surfeces, that have i-th coordionate x[i] such that x[i] == 0 or x[i] == size[i]
BorderConditions object recalculating istances between atoms
This class is realizing periodic borders and "none" borders (if border not defined in this direction)  */
class BorderConditions
{
private:
	enum class borderType {
		periodic,
		none,
	};
	borderType type[DIMENSIONAL_NUMBER];
	ProjectionTuple size;
public:
	/*isPeriodic Borders[i] determining whether there are periodic border conditions in i-th direction
	if isPeriodicBorders[i] == false the i-th direction not have borders
	size[i] is distance between borders in i-th direction. size[i] have sence if isPeriodicBorders[i] == true*/
	BorderConditions(ProjectionTuple& size, bool isPeriodicBorders[DIMENSIONAL_NUMBER]);
	double computeDistance(ProjectionTuple& projectionsDifference) const;
};

#endif	//TAHD_BORDER_CONDITIONS_H
