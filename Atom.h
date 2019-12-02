#pragma once
#ifndef TAHD_ATOM_H
#define TAHD_ATOM_H

#include "Elements.h"
#include "constants.h"
#include <string>
#include <cmath>

class Atom
{
private:
	static unsigned int nextId;
	static short unsigned int stepIndex;		//indexing steps: in a[stepIndex][] conteining actuality accelerations
	int id;
	element chemElement;
	double mass;
	double r[DIMENSIONAL_NUMBER];
	double v[DIMENSIONAL_NUMBER];
	double a[2][DIMENSIONAL_NUMBER];

	void computeMass();
	int createId() const;
	void constructing(double coordinates[DIMENSIONAL_NUMBER]);
	int getPreviousStepIndex() const;

public:
	Atom(element element, double coordinates[DIMENSIONAL_NUMBER]);
	Atom(char element, double coordinates[DIMENSIONAL_NUMBER]);
	Atom(char element[2], double coordinates[DIMENSIONAL_NUMBER]);
	Atom(std::string element, double coordinates[DIMENSIONAL_NUMBER]);
	static void changeStepIndex();
	void setCoordinates(double coordinates[DIMENSIONAL_NUMBER]);
	void setVelocity(double velocity[DIMENSIONAL_NUMBER]);
	void addVelocity(double adding_velocity[DIMENSIONAL_NUMBER]);
};

#endif	//TAHD_ATOM_H
