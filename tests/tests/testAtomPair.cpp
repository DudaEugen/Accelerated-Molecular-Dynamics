#include "../tests.hpp"
#include "Atoms/AtomPair.hpp"

using namespace md;

void testAtomPair()
{
    Atom a("Cu", randomPosition());
	Atom b("Al", randomPosition());
	AtomPair pair(a, b);

	assert(&a == &pair.getFirst());
	assert(&b == &pair.getSecond());
	Vector d = b.getPosition() - a.getPosition();
	auto [distance, projections] = pair.getDistanceWithProjections();
	assert(equal(d, projections));
	assert(equal(d.absoluteValue(), distance));

	b.setPosition(randomPosition());
	auto [distance2, projections2] = pair.computeDistanceWithProjections();
	d = b.getPosition() - a.getPosition();
	assert(equal(d, projections2));
	assert(equal(d.absoluteValue(), distance2));

	b.setPosition(a.getPosition());
	auto [distance3, projections3] = pair.computeDistanceWithProjections();
	assert(equal(distance3, 0));
	assert(equal(projections3, Vector()));
}
