#include "tests.hpp"

using namespace md;

void testVectorDimensionalNumber3()
{
    if constexpr (DimensionalNumber == 3)
	{
		assert(equal(
            Vector({ 3, 4, 0 }).absoluteValue(), 
            Vector({ -5, 0, 0 }).absoluteValue()
        ));
		assert(not equal(
            Vector({ -3, 4.00000001, 0 }).sumSquares(), 
            Vector({ 0, 0, -5 }).sumSquares()
        ));
		assert(equal(
            Vector({ 9.8765, -6.789654, 4.324109 }), 
            -Vector({ -9.8765, 6.789654, -4.324109 })
        ));
		assert(equal(
            Vector({ 4.5, -3.8, 100.000501 }) / 2, 
            Vector({ 2.25, -1.9, 50.0002505 })
        ));
		assert(equal(
            Vector({ 4, 6, 7 })[0], 
            Vector({ 1, 2, 4 })[2]
        ));
		assert(not equal(
            Vector({ 4, 6, 7 })[1], 
            Vector({ 1, -6, 4 })[1]
        ));
	}
}

void testVectorConstructors()
{
    // testing default constructor
    const Vector vect;
	Vector::projection_index j = 0;
	for (const double& value: vect)
	{
		assert(value == 0);
		++j;
	}
}

void testVectorOperators()
{
    Vector zero{};

	Vector v1 = randomVector();
	Vector v2 = v1;
	Vector v3 = randomVector();
	v3 = v2;

	assert(equal(v3, v1));
	assert(equal(2 * v1, v1 + v1));
	assert(equal(v1 - v1, zero));
	assert(equal(-v1, v1 - 2 * v1));
	assert(equal(v2 + v1 - 2 * v3, zero));

	v2 *= 2;
	v3 *= 3;
	assert(equal(v3 + v2, v1 * 5));

	v3 = v2 = v1;
	v2 /= 2;
	v3 /= 3;
	assert(equal(v2 - v3, v1 / 6));

	v3 = v2 = v1;
	v3 += v2;
	v2 -= v3;
	assert(equal(v2 + v1, zero / 6 - v3 * 0));
}

void testVectorIterators()
{
    Vector vect1 = randomVector();
	Vector::projection_index i = 0;
	for (double& value: vect1)
	{
		assert(value == vect1[i]);
		value = -vect1[i];
		assert(value == vect1[i]);
		vect1[i] *= -1;
		assert(value == vect1[i]);
		++i;
	}
}

void testVector()
{
    testVectorConstructors();
    testVectorIterators();
    testVectorOperators();
    if constexpr (DimensionalNumber == 3)
    {
        testVectorDimensionalNumber3();
    }
}
