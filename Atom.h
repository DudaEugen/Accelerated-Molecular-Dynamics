#pragma once
#ifndef TAHD_ATOM_H
#define TAHD_ATOM_H

#include <string>
#include <cmath>
#include "constants.h"
#include "Elements.h"
#include "ProjectionTuple.h"

class Atom
{
private:
	static short unsigned int stepIndex;		//indexing steps: in a[stepIndex][] conteining actuality accelerations
	const element chemElement;
	const double mass;
	ProjectionTuple r;
	ProjectionTuple v;
	ProjectionTuple a[2];

	double computeMass(element element);
	int getPreviousStepIndex() const;
public:
	Atom(element element, ProjectionTuple coordinates);
	Atom(char element, ProjectionTuple coordinates);
	Atom(char element[2], ProjectionTuple coordinates);
	Atom(std::string element, ProjectionTuple coordinates);
	static void changeStepIndex();
	void setCoordinates(ProjectionTuple coordinates);
	void setVelocity(ProjectionTuple velocity);
	void setAcceleration(ProjectionTuple acceleration);
	void addVelocity(ProjectionTuple addingVelocity);
	void addAcceleration(ProjectionTuple addingAcceleratrion);
	const ProjectionTuple& getCoordinates() const;
	const ProjectionTuple& getVelocity() const;
	const ProjectionTuple& getAcceleration() const;
	void doStepEuler(const double dt);
	void doStepVelocityVerlet(const double dt);
};

#endif	//TAHD_ATOM_H
