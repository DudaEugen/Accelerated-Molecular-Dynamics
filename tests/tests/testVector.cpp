#include "tests.hpp"
#include "Vector/Position.hpp"
#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"
#include "BoundaryConditions/DimensionsCondition/PeriodicDimension.hpp"

using namespace md;

namespace testVectorClass
{
	namespace constructors
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
				value = randomDouble();
			}

			const Vector vector = array;
			assertProjectionValues(vector, array.data());
		}

		void cStyleArray()
		{
			double array[kDimensionalNumber];
			for (auto& value: array)
			{
				value = randomDouble();
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
			double value = randomDouble();
			auto values = std::vector(kDimensionalNumber, 0.);
			values[0] = value;
			assertProjectionValues(Vector{value}, values);
		}

		void initializerListWithFourElements()
		{
			double value1 = randomDouble();
			double value2 = randomDouble();
			double value3 = randomDouble();
			double value4 = randomDouble();
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
				double value = randomDouble();
				values.push_back(value);
				projection = value;
			}
			assertProjectionValues(Vector{vector}, values);	
		}
	}

	namespace operators
	{
		void assign()
		{
			Vector vector0 = randomVector();
			Vector vector1 = randomVector();
			Vector vector2;
			vector2 = vector1 = vector0;

			assert(equalAll({vector0, vector1, vector2}));
			assert(vector0.data() != vector1.data());
			assert(vector0.data() != vector2.data());
			assert(vector1.data() != vector2.data());
		}

		void unaryMinus()
		{
			Vector vector = randomVector();
			Vector other = -vector;
			assert(equal(vector, -other));
		}

		void plusAssign()
		{
			Vector vector0 = randomVector();
			Vector vector1;
			Vector vector2;
			vector2 += vector1 += vector0;
			
			assert(equalAll({vector0, vector1, vector2}));
			assert(vector0.data() != vector1.data());
			assert(vector0.data() != vector2.data());
			assert(vector1.data() != vector2.data());
		}

		void plus()
		{
			Vector vector0 = randomVector();
			Vector vector1 = randomVector();
			Vector vector2 = randomVector();
			Vector init_vector1 = vector1;
			Vector init_vector2 = vector2;
			vector2 += vector1 += vector0;

			assert(equal(vector1, init_vector1 + vector0));
			assert(equal(vector2, init_vector2 + vector1));
		}

		void minusAssign()
		{
			Vector vector0 = randomVector();
			Vector vector1 = vector0;
			Vector vector2;
			Vector init_vector1 = vector1;
			vector0 -= vector1 -= vector2;

			assert(equal(vector0, Vector{}));
			assert(equal(vector1, init_vector1));
		}

		void difference()
		{
			Vector vector0 = randomVector();
			Vector vector1 = randomVector();
			Vector vector2 = randomVector();
			Vector init_vector1 = vector1;
			Vector init_vector2 = vector2;
			vector2 -= vector1 -= vector0;

			assert(equal(vector1, init_vector1 - vector0));
			assert(equal(vector2, init_vector2 - vector1));
		}

		void squareBrackets()
		{
			Vector vector;
			for (unsigned i = 0; i < kDimensionalNumber; ++i)
			{
				double value = randomDouble();
				vector[i] = value;
				const Vector constVector = vector;
				assert(equal(vector[i], value));
				assert(equal(constVector[i], value));
			}
		}

		void productAssign()
		{
			Vector vector = randomVector();
			Vector init_vector = vector;
			double factor = randomDouble();
			vector *= factor;
			
			for (unsigned i = 0; i < kDimensionalNumber; ++i)
			{
				assert(equal(vector[i], init_vector[i]*factor));
			}
		}

		void product()
		{
			Vector vector0 = randomVector();
			Vector vector1 = vector0;
			double factor = randomDouble();
			vector1 *= factor;
			assert(equalAll({vector1, factor*vector0, vector0*factor}));
		}

		void divideAssign()
		{
			Vector vector = randomVector();
			Vector init_vector = vector;
			double divider = randomDouble();
			vector /= divider;
			
			for (unsigned i = 0; i < kDimensionalNumber; ++i)
			{
				assert(equal(vector[i], init_vector[i] / divider));
			}
		}

		void divide()
		{
			Vector vector0 = randomVector();
			Vector vector1 = vector0;
			double divider = randomDouble();
			vector1 /= divider;
			assert(equal(vector1, vector0/divider));
		}
	}

	namespace methods
	{
		void data()
		{
			Vector vector;
			auto data = vector.data();
			for (Vector::projection_index i = 0; i < kDimensionalNumber; ++i)
			{
				data[i] = randomDouble();
				assert(equal(vector[i], data[i]));
			}
		}

		void dataConst()
		{
			const Vector vector = randomVector();
			auto data = vector.data();
			for (Vector::projection_index i = 0; i < kDimensionalNumber; ++i)
			{
				assert(equal(vector[i], data[i]));
			}
		}

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

	namespace iterators
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
			double new_value = randomDouble();
			value = new_value;
			assert(equal(vector[i], new_value));
			++i;
		}
	}
}
}

namespace testPositionClass
{
	namespace constructors
	{
		void defaultCtr()
		{
			const Position position;
			const Vector vector;
			assert(equal(vector, position));
		}

		void array()
		{
			std::array<double, kDimensionalNumber> array;
			for (auto& value: array)
			{
				value = randomDouble();
			}

			const Position position = array;
			const Vector vector = array;
			assert(equal(vector, position));
		}

		void cStyleArray()
		{
			double array[kDimensionalNumber];
			for (auto& value: array)
			{
				value = randomDouble();
			}

			const Position position = array;
			const Vector vector = array;
			assert(equal(vector, position));
		}
	}

	namespace boundaryConditions
	{
		void resetBoundaryConditions()
		{
			IDimensionsCondition* conditions[kDimensionalNumber];
			for (uint8_t i = 0; i < kDimensionalNumber; ++i) {
				conditions[i] = new InfiniteDimension();
			}
			Position::setBoundaryConditions(conditions);
		}

		void infiniteSpace()
		{
			IDimensionsCondition* conditions[kDimensionalNumber];
			for (uint8_t i = 0; i < kDimensionalNumber; ++i) {
				conditions[i] = new InfiniteDimension();
			}
			Position::setBoundaryConditions(conditions);

			Position firstPosition;
			Position secondPosition;
			firstPosition += randomVector();
			secondPosition += randomVector();
			Vector difference = static_cast<Vector>(firstPosition) - static_cast<Vector>(secondPosition);
			auto [distance, projections] = firstPosition.distanceWithProjectionsTo(secondPosition);

			assert(equal(distance, difference.absoluteValue()));
			assert(equal(projections, difference));

			resetBoundaryConditions();
		}

		void periodicSpace()
		{
			double size = randomDouble<1, 10>();
			IDimensionsCondition* conditions[kDimensionalNumber];
			for (uint8_t i = 0; i < kDimensionalNumber; ++i) {
				conditions[i] = new PeriodicDimension(size);
			}
			Position::setBoundaryConditions(conditions);

			Position firstPosition;
			Position secondPosition;
			firstPosition += randomVector();
			secondPosition += randomVector();
			auto [_, projections] = firstPosition.distanceWithProjectionsTo(secondPosition);

			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
			{
				assert(std::abs(projections[i]) <= size);
			}

			resetBoundaryConditions();
		}
	}
}

void testVector()
{
	testVectorClass::constructors::array();
	testVectorClass::constructors::copyCtr();
	testVectorClass::constructors::cStyleArray();
	testVectorClass::constructors::defaultCtr();
	testVectorClass::constructors::emptyInitializerList();
	testVectorClass::constructors::initializerListWithFourElements();
	testVectorClass::constructors::initializerListWithOneElement();

	testVectorClass::operators::assign();
	testVectorClass::operators::unaryMinus();
	testVectorClass::operators::plusAssign();
	testVectorClass::operators::plus();
	testVectorClass::operators::minusAssign();
	testVectorClass::operators::difference();
	testVectorClass::operators::squareBrackets();
	testVectorClass::operators::product();
	testVectorClass::operators::productAssign();
	testVectorClass::operators::divide();
	testVectorClass::operators::divideAssign();

	testVectorClass::methods::data();
	testVectorClass::methods::dataConst();
	testVectorClass::methods::absoluteValue();
	testVectorClass::methods::size();
	testVectorClass::methods::sumSquares();

	testVectorClass::iterators::constIterator();
	testVectorClass::iterators::iterator();

	testPositionClass::constructors::array();
	testPositionClass::constructors::cStyleArray();
	testPositionClass::constructors::defaultCtr();

	testPositionClass::boundaryConditions::infiniteSpace();
	testPositionClass::boundaryConditions::periodicSpace();
}
