#include "tests.hpp"

using namespace md;

namespace testVectorConstructors
{
	void assertProjectionValues(Vector::ConstPass vector, const std::vector<double>& values)
	{
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			if (i < values.size())
			{
				assert(equal(vector[i], values[i]));
			}
			else
			{
				assert(equal(vector[i], 0));
			}
		}
	}

	void assertProjectionValues(Vector::ConstPass vector, double const * const values)
	{
		assertProjectionValues(vector, std::vector(values, values + kDimensionalNumber));
	}

	void defaultCtr()
	{
		const Vector vect;
		assertProjectionValues(vect, std::vector(kDimensionalNumber, 0.));
	}

	void array()
	{
		std::array<double, kDimensionalNumber> array;
		for (auto& value: array)
		{
			value = random();
		}

		const Vector vector = array;
		assertProjectionValues(vector, array.data());
	}

	void cStyleArray()
	{
		double array[kDimensionalNumber];
		for (auto& value: array)
		{
			value = random();
		}

		const Vector vector = array;
		assertProjectionValues(vector, array);
	}

	void emptyInitializerList()
	{
		assertProjectionValues(Vector{{}}, std::vector(kDimensionalNumber, 0.));
	}

	void initializerListWithOneElement()
	{
		double value = random();
		auto values = std::vector(kDimensionalNumber, 0.);
		values[0] = value;
		assertProjectionValues(Vector{value}, values);
	}

	void initializerListWithFourElements()
	{
		double value1 = random();
		double value2 = random();
		double value3 = random();
		double value4 = random();
		assertProjectionValues(
			Vector{value1, value2, value3, value4},
			std::vector{value1, value2, value3, value4}
		);
	}

	void copyCtr()
	{
		std::vector<double> values;
		md::Vector vector;
		for (auto& projection: vector)
		{
			double value = random();
			values.push_back(value);
			projection = value;
		}
		assertProjectionValues(Vector{vector}, values);	
	}
}

namespace testVectorOperators
{
	void assign()
	{
		Vector vector = randomVector();
		Vector copy_vector1, copy_vector2;
		copy_vector2 = copy_vector1 = vector;
		assert(equalAll(std::vector{vector, copy_vector1, copy_vector2}));
	}

	void unaryMinus()
	{
		Vector vector = randomVector();
		Vector other = -vector;
		assert(equal(vector, -other));

		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			assert(equal(other[i], -vector[i]));
		}
	}

	void plusAssign()
	{
		Vector vector0 = randomVector();
		Vector vector1;
		vector1 += vector0;
		assert(equal(vector0, vector1));

		vector1 = randomVector();
		Vector vector2 = randomVector();
		Vector init_vector1 = vector1;
		Vector init_vector2 = vector2;
		vector2 += vector1 += vector0;
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			assert(equal(vector2[i], init_vector2[i] + vector1[i]));
			assert(equal(vector1[i], init_vector1[i] + vector0[i]));
		}
	}

	void minusAssign()
	{
		Vector vector0 = randomVector();
		Vector vector1 = vector0;
		vector1 -= vector0;
		assert(equal(vector1, Vector{}));

		vector1 = randomVector();
		Vector vector2 = randomVector();
		Vector init_vector1 = vector1;
		Vector init_vector2 = vector2;
		vector2 -= vector1 -= vector0;
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			assert(equal(vector2[i], init_vector2[i] - vector1[i]));
			assert(equal(vector1[i], init_vector1[i] - vector0[i]));
		}
	}

	void productAssign()
	{
		Vector vector = randomVector();
		Vector init_vector = vector;
		double factor = random();
		vector *= factor;
		
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			assert(equal(vector[i], init_vector[i]*factor));
		}
	}

	void divideAssign()
	{
		Vector vector = randomVector();
		Vector init_vector = vector;
		double divider = random();
		vector /= divider;
		
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			assert(equal(vector[i], init_vector[i] / divider));
		}
	}

	void squareBrackets()
	{
		Vector vector;
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			double value = random();
			vector[i] = value;
			const Vector constVector = vector;
			assert(equal(vector[i], value));
			assert(equal(constVector[i], value));
		}
	}

	void plus()
	{
		Vector vector0;
		Vector vector1;
		Vector summ = vector1 + vector0;
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			assert(equal(summ[i], vector0[i] + vector1[i]));
		}
	}

	void difference()
	{
		Vector vector0;
		Vector vector1;
		Vector difference = vector1 + vector0;
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			assert(equal(difference[i], vector1[i] - vector0[i]));
		}
	}

	void product()
	{
		Vector vector0 = randomVector();
		Vector vector1 = vector0;
		double factor = random();
		vector1 *= factor;
		assert(equalAll(std::vector{vector1, factor*vector0, vector0*factor}));
	}

	void divide()
	{
		Vector vector0 = randomVector();
		Vector vector1 = vector0;
		double divider = random();
		vector1 /= divider;
		assert(equal(vector1, vector0/divider));
	}
}

namespace testVectorMethods
{
	void size()
	{
		assert(Vector{}.size() == kDimensionalNumber);
	}

	void sumSquares()
	{
		Vector vector = randomVector();
		double sumSquares = 0;
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			sumSquares += vector[i] * vector[i];
		}
		assert(equal(vector.sumSquares(), sumSquares));
	}

	void absoluteValue()
	{
		Vector vector = randomVector();
		double sumSquares = 0;
		for (unsigned i = 0; i < kDimensionalNumber; ++i)
		{
			sumSquares += vector[i] * vector[i];
		}
		assert(equal(vector.absoluteValue(), std::sqrt(sumSquares)));
	}
}

namespace testVectorIterators
{
	void constIterator()
	{
		const Vector vector = randomVector();
		Vector::projection_index i = 0;
		for (auto value: vector)
		{
			assert(equal(vector[i], value));
			++i;
		}
	}
	
	void iterator()
	{
		Vector vector = randomVector();
		Vector::projection_index i = 0;
		for (auto& value: vector)
		{
			assert(equal(vector[i], value));
			double new_value = random();
			value = new_value;
			assert(equal(vector[i], new_value));
			++i;
		}
	}
}

void testVector()
{
	testVectorConstructors::array();
	testVectorConstructors::copyCtr();
	testVectorConstructors::cStyleArray();
	testVectorConstructors::defaultCtr();
	testVectorConstructors::emptyInitializerList();
	testVectorConstructors::initializerListWithFourElements();
	testVectorConstructors::initializerListWithOneElement();

	testVectorOperators::assign();
	testVectorOperators::difference();
	testVectorOperators::divide();
	testVectorOperators::divideAssign();
	testVectorOperators::minusAssign();
	testVectorOperators::plus();
	testVectorOperators::plusAssign();
	testVectorOperators::product();
	testVectorOperators::productAssign();
	testVectorOperators::squareBrackets();
	testVectorOperators::unaryMinus();

	testVectorMethods::absoluteValue();
	testVectorMethods::size();
	testVectorMethods::sumSquares();

	testVectorIterators::constIterator();
	testVectorIterators::iterator();
}
