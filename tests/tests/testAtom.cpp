#include "../tests.hpp"
#include "Atoms/Atom.hpp"

using namespace md;

void testAtomDimensionalNumber3()
{
    if constexpr (DimensionalNumber == 3)
	{
        char c[2] = { 'A', 'u' };
        Vector v = randomVector();
        Atom a(c, randomVector());
		
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
	assert(md::get_atomic_mass(aAl_1.chemElement) == 27);
	assert(equal(aAl_1.mass, md::get_atomic_mass(aAl_2.chemElement) / (K_Avogadro * 1000)));

    char c[2] = { 'A', 'u' };
	assert(md::get_atomic_mass(Atom(c, randomVector()).chemElement) == 197);
	assert(md::get_atomic_number(Atom(c, randomVector()).chemElement) == 79);

    Vector v = aAl_1.getCoordinates();
	Atom a(c, v);
	assert(equal(a.getCoordinates(), aAl_1.getCoordinates()));
	assert(equal(a.getAcceleration(), randomVector() * 0));
}

void testAtomMoving()
{
    Vector rx = randomVector();
	Vector rv = randomVector();
	Vector ra = randomVector();
	Atom a1("Cu", Vector());
	Atom a2("Cu", Vector());
	a2.setVelocity(rv);
	Atom a3("Cu", Vector());	
	Atom a4("Al", rx);
	a4.setVelocity(rv);
	a4.addVelocity(rv);
	Atom a5("Au", Vector());
	double dt = 0.000'01;
	for(int i = 0; i < 100'000; ++i)
	{
		a1.move(dt);
		a2.move(dt);
		a3.setAcceleration(ra);
		a3.move(dt);
		a4.setAcceleration(Vector());
		a4.addAcceleration(ra);
		a4.move(dt);
		a5.setAcceleration(ra * (1 - i * dt));
		a5.move(dt);
	}
	assert(equal(a1.getCoordinates(), Vector(), 3));
	assert(equal(a2.getCoordinates(), rv, 3));
	assert(equal(a3.getCoordinates(), ra / 2, 3));
	assert(equal(a4.getCoordinates(), rx + 2*rv + ra / 2, 3));
	assert(equal(a5.getCoordinates(), ra / 2 - ra / 6, 3));
}

void testAtom()
{
    testAtomConstructors();
    testAtomMoving();
	if constexpr (DimensionalNumber == 3)
	{
		testAtomDimensionalNumber3();
	}
}
