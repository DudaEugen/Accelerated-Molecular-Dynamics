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

	double computeMass(const element element);
	int getPreviousStepIndex() const;
public:
	Atom(const element element, const ProjectionTuple coordinates);
	Atom(const char element, const ProjectionTuple coordinates);
	Atom(const char element[2], const ProjectionTuple coordinates);
	Atom(const std::string element, const ProjectionTuple coordinates);
	static void changeStepIndex();
	void setCoordinates(const ProjectionTuple coordinates);
	void setVelocity(const ProjectionTuple velocity);
	void setAcceleration(const ProjectionTuple acceleration);
	void addVelocity(const ProjectionTuple addingVelocity);
	void addAcceleration(const ProjectionTuple addingAcceleratrion);
	const ProjectionTuple& getCoordinates() const;
	const ProjectionTuple& getVelocity() const;
	const ProjectionTuple& getAcceleration() const;
	void doStepEuler(const double dt);
	void doStepVelocityVerlet(const double dt);
};

#endif	//TAHD_ATOM_H
