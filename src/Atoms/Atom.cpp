#include "Atoms/Atom.hpp"
#include <tuple> 
#include "Atoms/MoveAlgorithm/Frozen.hpp"
#include "Atoms/MoveAlgorithm/VelocityVerlet.hpp"

md::Atom::Atom(
	element element,
	Vector::ConstPass coordinates,
	Vector::ConstPass velocity,
	bool isFrozen
):
	chemElement{ element }, 
	mass{ computeMass(element) },
	coordinates{ coordinates }, 
	velocity{ velocity },
	acceleration{}
{
	if (isFrozen)
		moveAlgorithm = new Frozen();
	else
		moveAlgorithm = new VelocityVerlet();
}

md::Atom::Atom(
	const std::string_view element,
	Vector::ConstPass coordinates,
	Vector::ConstPass velocity,
	bool isFrozen
):
	Atom{ parseElement(element), coordinates, velocity, isFrozen }
{
}

md::Atom::Atom(
	element element,
	Vector::ConstPass coordinates,
	bool isFrozen
):
	Atom{ element, coordinates, {}, isFrozen }
{
}

md::Atom::Atom(
	const std::string_view element,
	Vector::ConstPass coordinates,
	bool isFrozen
):
	Atom{ parseElement(element), coordinates, {}, isFrozen }
{
}

md::Atom::Atom(const Atom& other)
	: Atom{other.chemElement, other.coordinates, other.velocity, other.isFrozen()}
{
}

md::Atom::~Atom()
{
	delete moveAlgorithm;
}

double md::Atom::computeMass(element element) 
{
	unsigned aMass;
	if constexpr (kUseAverageAtomicMass)
		aMass = atomicMass(element).average();
	else
		aMass = atomicMass(element).random();
	return aMass * 0.001 / kAvogadro; 
}

void md::Atom::setCoordinates(Vector::ConstPass newCoordinates) noexcept
{
	coordinates = newCoordinates;
}

void md::Atom::setVelocity(Vector::ConstPass newVelocity) noexcept
{
	velocity = newVelocity;
}

void md::Atom::setAcceleration(Vector::ConstPass nawAcceleration) noexcept 
{ 
	acceleration = nawAcceleration; 
}

md::Vector::ConstPass md::Atom::getCoordinates() const noexcept
{
	return coordinates;
}

md::Vector::ConstPass md::Atom::getVelocity() const noexcept
{
	return velocity;
}

md::Vector::ConstPass md::Atom::getAcceleration() const noexcept
{
	return acceleration;
}

void md::Atom::addAcceleration(Vector::ConstPass addingAcceleration) noexcept 
{ 
	acceleration += addingAcceleration; 
}

void md::Atom::applyForce(Vector::ConstPass force) 
{ 
	addAcceleration(force / mass);
}

void md::Atom::move(double deltaTime) noexcept
{
	std::tie(coordinates, velocity) = moveAlgorithm->move(
		coordinates, velocity, acceleration, deltaTime
	);
}

bool md::Atom::isFrozen() const
{
	return typeid(*moveAlgorithm) == typeid(Frozen);
}
