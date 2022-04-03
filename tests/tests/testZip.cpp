#include "../tests.hpp"
#include "Zip.hpp"
#include "IndexedZip.hpp"

using namespace utils::zip;
using namespace md;

void testUnindexedZip()
{
    Vector v1 = randomVector();
	Vector v2 = randomVector();
	std::array<int, kDimensionalNumber> arr;
	for(auto& v: arr)
		v = randomDouble();
	
	Vector::projection_index i = 0;
	for (auto [a, b, c]: Zip(v1, v2, std::as_const(arr)))
	{
		assert(equal(a, v1[i]));
		assert(equal(b, v2[i]));
		a = 1;
		assert(equal(v1[i], 1));
		a = -1;
		assert(equal(v1[i], -1));
		assert(c == arr[i]);
		++i;
	}
	assert(i == kDimensionalNumber);
}

void testIndexedZip()
{
    Vector v1 = randomVector();
	Vector v2 = randomVector();
	std::array<int, kDimensionalNumber> arr;
	for(auto& v: arr)
		v = randomDouble();

    for (auto [index, a, b]: IndexedZip(v1, arr))
	{
		assert(equal(a, v1[index]));
		assert(b == arr[index]);
		assert(index >= 0 && index < kDimensionalNumber);
	}

	std::vector<std::size_t> v = {10, 20, 30 , 40, 50, 60, 70, 80, 90};
	Vector::projection_index i = 0;
	for (auto [index, p]: IndexedZip(v))
	{
		assert(p == 10*(index + 1));
		++i;
	}
	assert(i == v.size());

	for (auto [index, a, b, c]: IndexedZip(v1, arr, v2))
		assert(index < kDimensionalNumber);
	for (auto [index, a, b, c, p]: IndexedZip(v1, arr, v2, v))
		assert(index < kDimensionalNumber);
	std::array<int, 3> dd = {};
	for (auto [index, a, b, c, p, d]: IndexedZip(v1, arr, v2, v, dd))
		assert(index < kDimensionalNumber);
}

void testZip()
{
    testUnindexedZip();
    testIndexedZip();	
}
