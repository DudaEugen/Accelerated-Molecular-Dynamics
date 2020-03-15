#pragma once
#ifndef TAHD_ATOM_H
#define TAHD_ATOM_H

#include <string>
#include <cmath>
#include "constants.h"
#include "Elements.h"
#include "Vector.h"

class Atom
{
private:
	static short unsigned int stepIndex;		/*indexing steps: a[stepIndex] containing actuality accelerations
												  a[not stepIndex] containing accelerations corresponding previous step*/
public:
	const element chemElement;
	const double mass;
private:
	Vector r;
	Vector v;
	Vector a[2];

	double computeMass(const element element);
	int getPreviousStepIndex() const;
public:
	Atom(const element element, Vector::ConstVectorPass coordinates);
	Atom(const char element, Vector::ConstVectorPass coordinates);
	Atom(const char element[2], Vector::ConstVectorPass coordinates);
	Atom(const std::string element, Vector::ConstVectorPass coordinates);
	static void changeStepIndex();				/*the class invoking doStepVelocityVerlet method is responsible for calling changeStepIndex()
												  after ever call doStepVelocityVerlet for all atoms*/
	void setCoordinates(Vector::ConstVectorPass coordinates);
	void setVelocity(Vector::ConstVectorPass velocity);
	void setAcceleration(Vector::ConstVectorPass acceleration);
												//addQuantity methods are adding argument to actuality value of quantity
	void addVelocity(Vector::ConstVectorPass addingVelocity);
	void addAcceleration(Vector::ConstVectorPass addingAcceleratrion);
	Vector::ConstVectorPass getCoordinates() const;
	Vector::ConstVectorPass getVelocity() const;
	Vector::ConstVectorPass getAcceleration() const;
												//doStepAlhorithm are methods to moving atom corresponding algorithm
	void doStepEuler(const double dt);
	void doStepVelocityVerlet(const double dt);	//dont first step
};

#endif	//TAHD_ATOM_H
