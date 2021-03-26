#include "../tests.hpp"
#include "Atoms/Atom.hpp"

using namespace md;

void testAtomkDimensionalNumber3()
{
    if constexpr (kDimensionalNumber == 3)
	{
        Vector v = randomVector();
        Atom a(element::Au, randomVector());
		
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
    Atom aAl_1(element::Al, randomVector());
	Atom aAl_2(element::Al, randomVector());
	Atom aCu_1(element::Cu, randomVector());
	Atom aCu_2 = aCu_1;
	assert(aAl_1.chemElement == aAl_2.chemElement);
	assert(aCu_1.chemElement == aCu_2.chemElement);
	assert(not(aAl_1.chemElement == aCu_2.chemElement));
	assert(md::get_atomic_mass(aAl_1.chemElement) == 27);
	assert(equal(aAl_1.mass, md::get_atomic_mass(aAl_2.chemElement) / (kAvogadro * 1000)));

	assert(md::get_atomic_mass(Atom(element::Au, randomVector()).chemElement) == 197);
	assert(md::get_atomic_number(Atom(element::Au, randomVector()).chemElement) == 79);

    Vector v = aAl_1.getCoordinates();
	Atom a(element::Au, v);
	assert(equal(a.getCoordinates(), aAl_1.getCoordinates()));
	assert(equal(a.getAcceleration(), randomVector() * 0));
}

void testAtomMoving()
{
    Vector rx = randomVector();
	Vector rv = randomVector();
	Vector ra = randomVector();
	Atom a1(element::Cu, Vector());
	Atom a2(element::Cu, Vector());
	a2.setVelocity(rv);
	Atom a3(element::Cu, Vector());	
	Atom a4(element::Al, rx);
	a4.setVelocity(rv);
	a4.addVelocity(rv);
	Atom a5(element::Au, Vector());
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
	if constexpr (kDimensionalNumber == 3)
	{
		testAtomkDimensionalNumber3();
	}
}
