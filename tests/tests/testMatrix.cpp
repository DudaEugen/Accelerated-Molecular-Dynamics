#include "../tests.hpp"
#include "Matrix/SquareMatrix.hpp"

using namespace utils::matrix;

void testMatrix()
{
	SquareMatrix<2> m1 = { {0, 1}, 
	                       {2, 3} };
	SquareMatrix<2> m2 = { {3, -4}, 
	                       {0.5, 6} };
	assert(equal(det(m1), -2));
	assert(equal(det(m2), 20));
	assert(equal(det(m1 + m2), 1. / det(invertible(m1+m2))));
	assert(equal((m1 * m2)[0][1], 6));
	m1[1][0] = 0;
	assert(equal(det(m1), 0));
	m2 /= 2;
	assert(equal(det(m2), 5));
	m2[0][0] *= 3;
	m2[1][0] *= 3;
	assert(equal(det(m2), 15));
	
	SquareMatrix<4> A = { {3.6, -7.8, 0, 2.5},
						   {7.6, -9, 11,  37},
						   {-2, 1.01, 0.345, -0.012504},
						   {34, 0, 3, 6} };
	ColumnMatrix<4> B = { 2, -7.4, 5, 7 };
	ColumnMatrix<4> X = invertible(A) * B;
	assert(equal(X[0], -5932236181. / 16361123414));
	assert(equal(X[1], -20634189316. / 8180561707));
	assert(equal(X[2], 159830004842. / 8180561707));
	assert(equal(X[3], -53563011250. / 8180561707));
	assert(equal(det(A), 1. / det(invertible(A))));
	assert(equal(A[2][3], transponse(A)[3][2]));
}
