#include "../tests.hpp"
#include "Atoms/Atom.hpp"

using namespace md;

namespace testAtomMethods
{
	void testAcceleration()
	{
		Vector initialAcceleration = randomVector();
		Vector additionalAcceleration = randomVector();

		Atom atom("Au", randomPosition());
		atom.setAcceleration(initialAcceleration);
		atom.addAcceleration(additionalAcceleration);

		assert(equal(atom.getAcceleration(), initialAcceleration + additionalAcceleration));
	}

	void testFrozen()
	{
		Position initialCoordinates = randomPosition();
		Atom atom(element::Cu, initialCoordinates, randomVector(), true);
		atom.setAcceleration(randomVector());

		assert(atom.isFrozen());
		assert(equal(atom.getPosition(), initialCoordinates));
	}

	void testMass()
	{
		Atom atom1("Al", randomPosition());
		assert(atom1.chemElement == element::Al);
		assert(equal(atom1.mass, md::atomicMass(element::Al).average() / (kAvogadro * 1000)));

		Atom atom2(element::I, randomPosition());
		assert(atom2.chemElement == element::I);
		assert(equal(
			atom1.mass / atom2.mass,
			static_cast<double>(md::atomicMass(atom1.chemElement).average()) / md::atomicMass(atom2.chemElement).average()
		));
	}

	void testMove()
	{
		Position initialCoordinates = randomPosition();
		Vector initialVelocity = randomPosition();
		Vector acceleration = randomVector();
		Atom atom("O", initialCoordinates, initialVelocity);
		assert(!atom.isFrozen());

		atom.setAcceleration(acceleration);
		int count = static_cast<int>(randomDouble<100, 1000>());

		for (int i = 0; i < count; ++i)
		{
			atom.move(1./count);
		}

		assert(equal(atom.getVelocity(), initialVelocity + acceleration, 3));
		assert(equal(
			atom.getPosition(),
			initialCoordinates + initialVelocity + 0.5 * acceleration,
			3
		));
	}

	void testApplyForce()
	{
		Vector force = randomVector();
		Atom atom(element::Au, {});
		atom.applyForce(force);
		assert(equal(atom.getAcceleration() * atom.mass, force));
	}
}

void testAtom()
{
    testAtomMethods::testAcceleration();
	testAtomMethods::testFrozen();
	testAtomMethods::testMass();
	testAtomMethods::testMove();
	testAtomMethods::testApplyForce();
}
