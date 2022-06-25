#include "../tests.hpp"
#include "Atoms/AtomPair.hpp"

using namespace md;

namespace testAtomPairMethods
{
	void testConstructor()
	{
		Atom a("Cu", randomPosition());
		Atom b("Al", randomPosition());
		AtomPair pair(a, b);

		assert(&a == &pair.getFirst());
		assert(&b == &pair.getSecond());
	}

	void testGetDistanceWithProjections()
	{
		Atom a("Cu", randomPosition());
		Atom b("Cu", randomPosition());
		AtomPair pair(a, b);

		Vector expectedProjections = b.getPosition() - a.getPosition();
		auto [distance, projections] = pair.getDistanceWithProjections();
		assert(equal(projections, expectedProjections));
		assert(equal(distance, expectedProjections.absoluteValue()));
		assert(equal(pair.getDistance(), expectedProjections.absoluteValue()));
		assert(equal(pair.getProjections(), expectedProjections));
	}

	void testComputeDistanceWithProjections()
	{
		Atom a("Cu", randomPosition());
		Atom b("Cu", randomPosition());
		AtomPair pair(a, b);

		b.setPosition(randomPosition());
		Vector expectedProjections = b.getPosition() - a.getPosition();

		auto [oldDistance, oldProjections] = pair.getDistanceWithProjections();
		assert(!equal(oldProjections, expectedProjections));
		assert(!equal(oldDistance, expectedProjections.absoluteValue()));

		pair.computeDistanceWithProjections();
		auto [distance, projections] = pair.getDistanceWithProjections();
		assert(equal(projections, expectedProjections));
		assert(equal(distance, expectedProjections.absoluteValue()));
	}

	void testZeroDistance()
	{
		Atom a("Cu", randomPosition());
		Atom b("Cu", a.getPosition());
		AtomPair pair(a, b);

		auto [distance, projections] = pair.getDistanceWithProjections();
		assert(equal(projections, Vector()));
		assert(equal(distance, 0));
	}
}

void testAtomPair()
{
    testAtomPairMethods::testConstructor();
	testAtomPairMethods::testGetDistanceWithProjections();
	testAtomPairMethods::testComputeDistanceWithProjections();
	testAtomPairMethods::testZeroDistance();
}
