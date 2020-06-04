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
	bool isFirstStepTaken;
	char actualStepIndex;						/*indexing steps: a[actualStepIndex] containing actuality accelerations
												  a[not actualStepIndex] containing accelerations corresponding previous step*/

public:
	const element chemElement;
	const double mass;
private:
	Vector r;
	Vector v;
	Vector a[2];

	double computeMass(const element element);
	char getPreviousStepIndex();
	void changeStepIndex();
	void doStepEuler(const double dt);
	void doStepVelocityVerlet(const double dt);	//dont first step
public:
	Atom(const element element, Vector::ConstVectorPass coordinates);
	Atom(const char element, Vector::ConstVectorPass coordinates);
	Atom(const char element[2], Vector::ConstVectorPass coordinates);
	Atom(const std::string element, Vector::ConstVectorPass coordinates);
					
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
	void move(const double dt);
};

#endif	//TAHD_ATOM_H
