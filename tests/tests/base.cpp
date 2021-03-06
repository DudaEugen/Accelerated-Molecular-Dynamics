#include "../tests.hpp"
#include <cmath>

bool equal(double d1, double d2, int symbolCountAfterPoint)
{
	return static_cast<int>(abs(d1 - d2) * pow(10, symbolCountAfterPoint)) == 0;
}

bool equal(md::Vector::ConstPass v1, md::Vector::ConstPass v2, int symbolCountAfterPoint)
{	
	bool result = true;
	for (md::Vector::projection_index i = 0; i < md::kDimensionalNumber; ++i)
		result = result && equal(v1[i], v2[i], symbolCountAfterPoint);
	return result;
}
