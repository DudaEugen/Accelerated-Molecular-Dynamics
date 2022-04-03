#include <cmath>
#include "features/compare.hpp"

bool equal(double d1, double d2, int symbolCountAfterPoint)
{
	return static_cast<int>(std::abs(d1 - d2) * std::pow(10, symbolCountAfterPoint)) == 0;
}

bool equal(md::Vector::ConstPass v1, md::Vector::ConstPass v2, int symbolCountAfterPoint)
{	
	const double* data1 = v1.data();
	const double* data2 = v2.data();
	for (md::Vector::projection_index i = 0; i < md::kDimensionalNumber; ++i)
		if (!equal(data1[i], data2[i], symbolCountAfterPoint))
			return false;
	return true;
}

bool equalAll(const std::vector<md::Vector>& vectors, int symbolCountAfterPoint)
{
	if (vectors.size() < 2)
	{
		return true;
	}
	
	return equal(vectors[0], vectors[1]) &&
		   equalAll(std::vector<md::Vector>(vectors.begin() + 2, vectors.end()), symbolCountAfterPoint);
}
