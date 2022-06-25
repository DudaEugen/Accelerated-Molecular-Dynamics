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
	std::tie(distance, projections) = pair.computeDistanceWithProjections();
	d = b.getPosition() - a.getPosition();
	assert(equal(d, projections));
	assert(equal(d.absoluteValue(), distance));

	b.setPosition(a.getPosition());
	std::tie(distance, projections) = pair.computeDistanceWithProjections();
	assert(equal(distance, 0));
	assert(equal(projections, Vector()));
}
