#include "Atom.hpp"
#include <cmath>

Atom::Atom(const element element, Vector::ConstPass coordinates):
	actualStepIndex{ 0 },
	chemElement{ element }, 
	mass{ computeMass(element) },
	r{ coordinates }, 
	v{},	
	a{ Vector(), Vector() }
{
}

Atom::Atom(const char element, Vector::ConstPass coordinates) : Atom{ chem_element::parse(element), coordinates }
{
}

Atom::Atom(const char element[2], Vector::ConstPass coordinates) : Atom{ chem_element::parse(element), coordinates }
{
}

Atom::Atom(const std::string element, Vector::ConstPass coordinates) : Atom{ chem_element::parse(element), coordinates }
{
}

double Atom::computeMass(const element element) { return chem_element::get_atomic_mass(element) * 0.001 / N_AVOGADRO; }

char Atom::getPreviousStepIndex() noexcept
{
	return actualStepIndex == 0 ? 1 : 0;
}

void Atom::changeStepIndex() noexcept
{ 
	actualStepIndex = actualStepIndex == 0 ? 1 : 0;
}

void Atom::doStepVelocityVerlet(const double dt) noexcept
{
	r += v * dt + 0.5 * a[actualStepIndex] * pow(dt, 2);
	v += 0.5 * (a[actualStepIndex] + a[getPreviousStepIndex()]) * dt;
}

void Atom::setCoordinates(Vector::ConstPass coordinates) noexcept { r = coordinates; }

void Atom::setVelocity(Vector::ConstPass velocity) noexcept { v = velocity; }

void Atom::setAcceleration(Vector::ConstPass acceleration) noexcept { a[actualStepIndex] = acceleration; }

void Atom::addVelocity(Vector::ConstPass addingVelocity) noexcept { v += addingVelocity; }

void Atom::addAcceleration(Vector::ConstPass addingAcceleration) noexcept { a[actualStepIndex] += addingAcceleration; }

Vector::ConstPass Atom::getCoordinates() const noexcept { return r; }

Vector::ConstPass Atom::getVelocity() const noexcept { return v; }

Vector::ConstPass Atom::getAcceleration() const noexcept { return a[actualStepIndex]; }

void Atom::move(const double dt) noexcept
{
	doStepVelocityVerlet(dt);
	changeStepIndex();
}
