#include "Atom.h"

Atom::Atom(const element element, Vector::ConstVectorPass coordinates):
	isFirstStepTaken{ false },
	actualStepIndex{ 0 },
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

char Atom::getPreviousStepIndex()
{
	return actualStepIndex == 0 ? 1 : 0;
}

void Atom::changeStepIndex() 
{ 
	actualStepIndex = actualStepIndex == 0 ? 1 : 0;
}

void Atom::doStepEuler(const double dt)
{
	r += v * dt + 0.5 * a[actualStepIndex] * pow(dt, 2);
	v += a[actualStepIndex] * dt;
}

void Atom::doStepVelocityVerlet(const double dt)
{
	r += v * dt + 0.5 * a[actualStepIndex] * pow(dt, 2);
	v += 0.5 * (a[actualStepIndex] + a[getPreviousStepIndex()]) * dt;
}

void Atom::setCoordinates(Vector::ConstVectorPass coordinates) { r = coordinates; }

void Atom::setVelocity(Vector::ConstVectorPass velocity) { v = velocity; }

void Atom::setAcceleration(Vector::ConstVectorPass acceleration) { a[actualStepIndex] = acceleration; }

void Atom::addVelocity(Vector::ConstVectorPass addingVelocity) { v += addingVelocity; }

void Atom::addAcceleration(Vector::ConstVectorPass addingAcceleration) { a[actualStepIndex] += addingAcceleration; }

Vector::ConstVectorPass Atom::getCoordinates() const { return r; }

Vector::ConstVectorPass Atom::getVelocity() const { return v; }

Vector::ConstVectorPass Atom::getAcceleration() const { return a[actualStepIndex]; }

void Atom::move(const double dt)
{
	if (isFirstStepTaken)
	{
		doStepVelocityVerlet(dt);
	}
	else
	{
		doStepEuler(dt);
	}
	changeStepIndex();
}
