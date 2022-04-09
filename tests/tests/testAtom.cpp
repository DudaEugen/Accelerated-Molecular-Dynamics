#include "../tests.hpp"
#include "Atoms/Atom.hpp"

using namespace md;

void testAtomkDimensionalNumber3()
{
    if constexpr (kDimensionalNumber == 3)
	{
        Vector v = randomVector();
        Atom a("Au", randomVector());
		
        a.setVelocity(v);
		Vector v2 = { 4, -5.67, 9.23897 };
		a.addVelocity(v2);
		assert(equal(a.getVelocity(), v + v2));

		a.setAcceleration(v2);
		a.addAcceleration(v2 / 2);
		assert(equal(a.getAcceleration(), 1.5 * v2));
	}
}

void testAtomConstructors()
{
    Atom aAl_1("Al", randomVector());
	Atom aAl_2("Al", randomVector());
	Atom aCu_1("Cu", randomVector());
	Atom aCu_2 = aCu_1;
	assert(aAl_1.chemElement == aAl_2.chemElement);
	assert(aCu_1.chemElement == aCu_2.chemElement);
	assert(not(aAl_1.chemElement == aCu_2.chemElement));
	assert(md::atomicMass(aAl_1.chemElement).average() == 27);
	assert(equal(aAl_1.mass, 
				 md::atomicMass(aAl_2.chemElement).average() / (kAvogadro * 1000)
	));

	std::string c = "Au";
	assert(md::atomicMass(Atom(c, randomVector()).chemElement).average() == 197);
	assert(md::atomicNumber(Atom(c, randomVector()).chemElement) == 79);

    Vector v = aAl_1.getCoordinates();
	Atom a(c, v);
	assert(equal(a.getCoordinates(), aAl_1.getCoordinates()));
	assert(equal(a.getAcceleration(), randomVector() * 0));
}

void testAtom()
{
    testAtomConstructors();
	if constexpr (kDimensionalNumber == 3)
	{
		testAtomkDimensionalNumber3();
	}
}
