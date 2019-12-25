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
	static short unsigned int stepIndex;		/*indexing steps: a[stepIndex] containing actuality accelerations
												  a[not stepIndex] containing accelerations corresponding previous step*/
public:
	const element chemElement;
	const double mass;
private:
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
	static void changeStepIndex();				/*the class invoking doStepVelocityVerlet method is responsible for calling changeStepIndex()
												  after ever call doStepVelocityVerlet for all atoms*/
	void setCoordinates(const ProjectionTuple coordinates);
	void setVelocity(const ProjectionTuple velocity);
	void setAcceleration(const ProjectionTuple acceleration);
												//addQuantity methods are adding argument to actuality value of quantity
	void addVelocity(const ProjectionTuple addingVelocity);
	void addAcceleration(const ProjectionTuple addingAcceleratrion);
	const ProjectionTuple& getCoordinates() const;
	const ProjectionTuple& getVelocity() const;
	const ProjectionTuple& getAcceleration() const;
												//doStepAlhorithm are methods to moving atom corresponding algorithm
	void doStepEuler(const double dt);
	void doStepVelocityVerlet(const double dt);	//dont first step
};

#endif	//TAHD_ATOM_H
