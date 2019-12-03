#include "Atom.h"

short unsigned int Atom::stepIndex = 0;

Atom::Atom(const element element, const ProjectionTuple coordinates):
	chemElement{ element }, 
	mass{ computeMass(element) },
	r{ coordinates }, 
	v{},	
	a{ ProjectionTuple(), ProjectionTuple() }
{
}

Atom::Atom(const char element, const ProjectionTuple coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

Atom::Atom(const char element[2], const ProjectionTuple coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

Atom::Atom(const std::string element, const ProjectionTuple coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

double Atom::computeMass(const element element) { return get_atomic_mass(element) * 0.001 / N_AVOGADRO; }

int Atom::getPreviousStepIndex() const { return  stepIndex == 0 ? 1 : 0; }

void Atom::changeStepIndex() { stepIndex = stepIndex == 0 ? 1 : 0; }

void Atom::setCoordinates(const ProjectionTuple coordinates) { r = coordinates; }

void Atom::setVelocity(const ProjectionTuple velocity) { v = velocity; }

void Atom::setAcceleration(const ProjectionTuple acceleration) { a[stepIndex] = acceleration; }

void Atom::addVelocity(const ProjectionTuple addingVelocity) { v += addingVelocity; }

void Atom::addAcceleration(const ProjectionTuple addingAcceleratrion) { a[stepIndex] = addingAcceleratrion; }

const ProjectionTuple& Atom::getCoordinates() const { return r; }

const ProjectionTuple& Atom::getVelocity() const { return v; }

const ProjectionTuple& Atom::getAcceleration() const { return a[stepIndex]; }

void Atom::doStepEuler(const double dt)
{
	r += v * dt + 0.5 * a[stepIndex] * pow(dt, 2);
	v += a[stepIndex] * dt;
}

void Atom::doStepVelocityVerlet(const double dt)
{
	r += v * dt + 0.5 * a[stepIndex] * pow(dt, 2);
	v += 0.5 * (a[stepIndex] + a[getPreviousStepIndex()]) * dt;
}
