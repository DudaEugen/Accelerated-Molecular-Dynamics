#include "../tests.hpp"
#include "Atoms/AtomPair.hpp"

using namespace md;

void testAtomPair()
{
    Atom a("Cu", randomVector());
	Atom b("Al", randomVector());
	AtomPair pair(a, b);

	assert(&pair.getAtomByIndex(AtomPair::index::first) == &pair.getFirst());
	assert(&pair.getAtomByIndex(AtomPair::index::second) == &pair.getSecond());
	assert(&pair.getAtomWithAnotherIndex(AtomPair::index::second) == &pair.getFirst());
	assert(&pair.getAtomWithAnotherIndex(AtomPair::index::first) == &pair.getSecond());
	assert(&a == &pair.getFirst());
	assert(&b == &pair.getSecond());
	Vector d = b.getCoordinates() - a.getCoordinates(); 
	assert(equal(d, pair.getDistanceProjections()));
	assert(equal(sqrt(d.sumSquares()), pair.getDistance()));

	b.setCoordinates(randomVector());
	pair.computeDistance();
	d = b.getCoordinates() - a.getCoordinates();
	assert(equal(b.getCoordinates() - a.getCoordinates(), pair.getDistanceProjections()));
	assert(equal(sqrt(d.sumSquares()), pair.getDistance()));

	b.setCoordinates(a.getCoordinates());
	pair.computeDistance();
	assert(equal(pair.getDistance(), 0));
}
