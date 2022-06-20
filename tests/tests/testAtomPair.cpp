#include "../tests.hpp"
#include "Atoms/AtomPair.hpp"

using namespace md;

void testAtomPair()
{
    Atom a("Cu", randomPosition());
	Atom b("Al", randomPosition());
	AtomPair pair(a, b);

	assert(&pair.getAtomByIndex(AtomPair::index::first) == &pair.getFirst());
	assert(&pair.getAtomByIndex(AtomPair::index::second) == &pair.getSecond());
	assert(&pair.getAtomWithAnotherIndex(AtomPair::index::second) == &pair.getFirst());
	assert(&pair.getAtomWithAnotherIndex(AtomPair::index::first) == &pair.getSecond());
	assert(&a == &pair.getFirst());
	assert(&b == &pair.getSecond());
	Vector d = b.getPosition() - a.getPosition(); 
	assert(equal(d, pair.getDistanceProjections()));
	assert(equal(sqrt(d.sumSquares()), pair.getDistance()));

	b.setPosition(randomPosition());
	pair.computeDistance();
	d = b.getPosition() - a.getPosition();
	assert(equal(b.getPosition() - a.getPosition(), pair.getDistanceProjections()));
	assert(equal(sqrt(d.sumSquares()), pair.getDistance()));

	b.setPosition(a.getPosition());
	pair.computeDistance();
	assert(equal(pair.getDistance(), 0));
}
