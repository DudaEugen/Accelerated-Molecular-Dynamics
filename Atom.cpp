#include "Atom.h"

short unsigned int Atom::stepIndex = 0;

Atom::Atom(element element, ProjectionTuple coordinates): 
	chemElement{ element }, 
	mass{ computeMass(element) },
	r{ coordinates }, 
	v{},	
	a{ ProjectionTuple(), ProjectionTuple() }
{
}

Atom::Atom(char element, ProjectionTuple coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

Atom::Atom(char element[2], ProjectionTuple coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

Atom::Atom(std::string element, ProjectionTuple coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

double Atom::computeMass(element element) { return get_atomic_mass(element) * 0.001 / N_AVOGADRO; }

int Atom::getPreviousStepIndex() const { return  stepIndex == 0 ? 1 : 0; }

void Atom::changeStepIndex() { stepIndex = stepIndex == 0 ? 1 : 0; }

void Atom::setCoordinates(ProjectionTuple coordinates) { r = coordinates; }

void Atom::setVelocity(ProjectionTuple velocity) { v = velocity; }

void Atom::setAcceleration(ProjectionTuple acceleration) { a[stepIndex] = acceleration; }

void Atom::addVelocity(ProjectionTuple addingVelocity) { v += addingVelocity; }

void Atom::addAcceleration(ProjectionTuple addingAcceleratrion) { a[stepIndex] = addingAcceleratrion; }

const ProjectionTuple& Atom::getCoordinates() const { return r; }

const ProjectionTuple& Atom::getVelocity() const { return v; }

const ProjectionTuple& Atom::getAcceleration() const { return a[stepIndex]; }
