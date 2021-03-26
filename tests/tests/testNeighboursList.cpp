#include "../tests.hpp"
#include "Atoms/NeighboursList.hpp"

using namespace md;

void testNeighboursList()
{
    std::vector<Atom> l1;
	Vector v = randomVector();
	Vector d{};
	d[0] += 1;
	l1.push_back(Atom{element::Cu, v - 2*d});
	l1.push_back(Atom{element::Cu, v});
	l1.push_back(Atom{element::Cu, v + 2*d});
	l1.push_back(Atom{element::Cu, v + 4*d});

	std::vector<AtomPair> prs;
	prs.push_back(AtomPair(l1[0], l1[1]));
	prs.push_back(AtomPair(l1[0], l1[2]));
	prs.push_back(AtomPair(l1[0], l1[3]));
	prs.push_back(AtomPair(l1[1], l1[2]));
	prs.push_back(AtomPair(l1[1], l1[3]));
	prs.push_back(AtomPair(l1[0], l1[3]));

	NeighboursList nList{l1[1], 2};
	for (std::size_t i = 0; i < prs.size(); ++i)
		nList.addPair(prs[i]);

	assert(nList.getNeighboursOfAtom(l1[1]).size() == 3);
	assert(nList.getNeighboursOfAtom(l1[2]).size() == 2);
	assert(&nList.getNeighboursOfAtom(l1[2])[0].getNeighbourAtom() != &l1[2]);
	assert(&nList.getNeighboursOfAtom(l1[1])[2].getNeighbourAtom() != &l1[1]);
	assert(&nList.getNeighboursOfAtom(l1[1])[0].getPair() == &prs[0]);
	assert(&nList.getNeighboursOfAtom(l1[2])[1].getPair() == &prs[3]);
	assert(nList.getNeighboursOfAtom(l1[1])[1].getPair().getDistance() != 0);
	
	l1[1].setCoordinates(l1[2].getCoordinates());
	prs[3].computeDistance();
	assert(nList.getNeighboursOfAtom(l1[1])[1].getPair().getDistance() == 0);
}
