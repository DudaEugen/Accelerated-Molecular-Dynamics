#include "Atom.h"

short unsigned int Atom::stepIndex = 0;

Atom::Atom(const element element, Vector::ConstVectorPass coordinates):
	chemElement{ element }, 
	mass{ computeMass(element) },
	r{ coordinates }, 
	v{},	
	a{ Vector(), Vector() }
{
}

Atom::Atom(const char element, Vector::ConstVectorPass coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

Atom::Atom(const char element[2], Vector::ConstVectorPass coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

Atom::Atom(const std::string element, Vector::ConstVectorPass coordinates) : Atom{ convert_to_element(element), coordinates }
{
}

double Atom::computeMass(const element element) { return get_atomic_mass(element) * 0.001 / N_AVOGADRO; }

int Atom::getPreviousStepIndex() const { return  stepIndex == 0 ? 1 : 0; }

void Atom::changeStepIndex() { stepIndex = stepIndex == 0 ? 1 : 0; }

void Atom::setCoordinates(Vector::ConstVectorPass coordinates) { r = coordinates; }

void Atom::setVelocity(Vector::ConstVectorPass velocity) { v = velocity; }

void Atom::setAcceleration(Vector::ConstVectorPass acceleration) { a[stepIndex] = acceleration; }

void Atom::addVelocity(Vector::ConstVectorPass addingVelocity) { v += addingVelocity; }

void Atom::addAcceleration(Vector::ConstVectorPass addingAcceleratrion) { a[stepIndex] = addingAcceleratrion; }

Vector::ConstVectorPass Atom::getCoordinates() const { return r; }

Vector::ConstVectorPass Atom::getVelocity() const { return v; }

Vector::ConstVectorPass Atom::getAcceleration() const { return a[stepIndex]; }

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
