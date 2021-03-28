#include "Atoms/Atom.hpp"
#include <cmath>

md::Atom::Atom(element element, Vector::ConstPass coordinates):
	actualStepIndex{ 0 },
	chemElement{ element }, 
	mass{ computeMass(element) },
	r{ coordinates }, 
	v{},	
	a{ Vector(), Vector() }
{
}

md::Atom::Atom(char element, Vector::ConstPass coordinates) 
	: Atom{ parse(element), coordinates }
{
}

md::Atom::Atom(const char element[2], Vector::ConstPass coordinates) 
	: Atom{ parse(element), coordinates }
{
}

md::Atom::Atom(const std::string& element, Vector::ConstPass coordinates) : 
	Atom{ parse(element), coordinates }
{
}

double md::Atom::computeMass(element element) 
{ 
	return isotope_generator(element).compute_average_atomic_mass() * 0.001 / kAvogadro; 
}

char md::Atom::getPreviousStepIndex() noexcept
{
	return actualStepIndex == 0 ? 1 : 0;
}

void md::Atom::changeStepIndex() noexcept
{ 
	actualStepIndex = actualStepIndex == 0 ? 1 : 0;
}

void md::Atom::doStepVelocityVerlet(double dt) noexcept
{
	r += v * dt + 0.5 * a[actualStepIndex] * pow(dt, 2);
	v += 0.5 * (a[actualStepIndex] + a[getPreviousStepIndex()]) * dt;
}

void md::Atom::setCoordinates(Vector::ConstPass coordinates) noexcept { r = coordinates; }

void md::Atom::setVelocity(Vector::ConstPass velocity) noexcept { v = velocity; }

void md::Atom::setAcceleration(Vector::ConstPass acceleration) noexcept 
{ 
	a[actualStepIndex] = acceleration; 
}

void md::Atom::addVelocity(Vector::ConstPass addingVelocity) noexcept { v += addingVelocity; }

void md::Atom::addAcceleration(Vector::ConstPass addingAcceleration) noexcept 
{ 
	a[actualStepIndex] += addingAcceleration; 
}

md::Vector::ConstPass md::Atom::getCoordinates() const noexcept { return r; }

md::Vector::ConstPass md::Atom::getVelocity() const noexcept { return v; }

md::Vector::ConstPass md::Atom::getAcceleration() const noexcept { return a[actualStepIndex]; }

void md::Atom::move(double dt) noexcept
{
	doStepVelocityVerlet(dt);
	changeStepIndex();
}
