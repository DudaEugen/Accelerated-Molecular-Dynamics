#include "Atom.h"

short unsigned int Atom::stepIndex = 0;
unsigned int Atom::nextId = 0;

Atom::Atom(element element, double coordinates[DIMENSIONAL_NUMBER])
	: id(createId()), chemElement(element)
{
	constructing(coordinates);
}

Atom::Atom(char element, double coordinates[DIMENSIONAL_NUMBER])
	: id(createId()), chemElement(convert_to_element(element))
{
	constructing(coordinates);
}

Atom::Atom(char element[2], double coordinates[DIMENSIONAL_NUMBER])
	: id(createId()), chemElement(convert_to_element(element))
{
	constructing(coordinates);
}

Atom::Atom(std::string element, double coordinates[DIMENSIONAL_NUMBER])
	: id(createId()), chemElement(convert_to_element(element))
{
	constructing(coordinates);
}

void Atom::computeMass() { mass = get_atomic_mass(chemElement) * 0.001 / N_AVOGADRO; }

int Atom::createId() const 
{ 
	nextId++;
	return nextId - 1;
}

void Atom::setCoordinates(double coordinates[DIMENSIONAL_NUMBER])
{
	for (short unsigned int i = 0; i < DIMENSIONAL_NUMBER; i++)
	{
		r[i] = coordinates[i];
	}
}

void Atom::constructing(double coordinates[DIMENSIONAL_NUMBER])
{
	setCoordinates(coordinates);
	computeMass();
	for (short unsigned int i = 0; i < DIMENSIONAL_NUMBER; i++)
	{
		v[i] = 0;
		a[0][i] = 0;
		a[1][i] = 0;
	}
}

int Atom::getPreviousStepIndex() const { return  stepIndex == 0 ? 1 : 0; }
void Atom::changeStepIndex() { stepIndex = stepIndex == 0 ? 1 : 0; }

void Atom::setVelocity(double velocity[DIMENSIONAL_NUMBER])
{
	for (short unsigned int i = 0; i < DIMENSIONAL_NUMBER; i++)
	{
		v[i] = velocity[i];
	}
}

void Atom::addVelocity(double adding_velocity[DIMENSIONAL_NUMBER])
{
	for (short unsigned int i = 0; i < DIMENSIONAL_NUMBER; i++)
	{
		v[i] += adding_velocity[i];
	}
}
