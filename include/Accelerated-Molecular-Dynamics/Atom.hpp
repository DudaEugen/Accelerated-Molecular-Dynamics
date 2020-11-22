#pragma once
#ifndef TAHD_ATOM_H
#define TAHD_ATOM_H

#include <string>
#include <cmath>
#include "constants.hpp"
#include "Elements.hpp"
#include "Vector.hpp"

class Atom
{
private:
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
	char getPreviousStepIndex() noexcept;
	void changeStepIndex() noexcept;
	void doStepVelocityVerlet(const double dt) noexcept;
public:
	Atom(const element element, Vector::ConstVectorPass coordinates);
	Atom(const char element, Vector::ConstVectorPass coordinates);
	Atom(const char element[2], Vector::ConstVectorPass coordinates);
	Atom(const std::string element, Vector::ConstVectorPass coordinates);
					
	void setCoordinates(Vector::ConstVectorPass coordinates) noexcept;
	void setVelocity(Vector::ConstVectorPass velocity) noexcept;
	void setAcceleration(Vector::ConstVectorPass acceleration) noexcept;
												//addQuantity methods are adding argument to actuality value of quantity
	void addVelocity(Vector::ConstVectorPass addingVelocity) noexcept;
	void addAcceleration(Vector::ConstVectorPass addingAcceleratrion) noexcept;
	Vector::ConstVectorPass getCoordinates() const noexcept;
	Vector::ConstVectorPass getVelocity() const noexcept;
	Vector::ConstVectorPass getAcceleration() const noexcept;
												//doStepAlhorithm are methods to moving atom corresponding algorithm
	void move(const double dt) noexcept;
};

#endif	//TAHD_ATOM_H
