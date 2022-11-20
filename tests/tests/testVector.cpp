#include <limits>
#include <iostream>
#include "tests.hpp"
#include "Vector/Position.hpp"
#include "BoundaryConditions/BoundaryConditions.hpp"
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
		void spaceSize()
		{
			Vector space = randomVector<1, 100>();
			IDimensionsCondition* conditions[kDimensionalNumber];
			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i) {
				conditions[i] = new PeriodicDimension(space[i]);
			}
			BoundaryConditions::setConditions(conditions);

			assert(equal(Position::spaceSize(), space));

			resetBoundaryConditions();
		}

		void minimalValue()
		{
			Vector values = randomVector();
			IDimensionsCondition* conditions[kDimensionalNumber];
			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i) {
				conditions[i] = new PeriodicDimension(randomDouble(), values[i]);
			}
			BoundaryConditions::setConditions(conditions);

			assert(equal(Position::minimalValue(), values));

			resetBoundaryConditions();

			IDimensionsCondition* newConditions[kDimensionalNumber];
			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i) {
				newConditions[i] = new PeriodicDimension(randomDouble());
			}
			BoundaryConditions::setConditions(newConditions);

			assert(equal(Position::minimalValue(), Position()));

			resetBoundaryConditions();
		}

		void infiniteSpace()
		{
			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i) {
				assert(Position::spaceSize()[i] == std::numeric_limits<double>::infinity());
				assert(Position::minimalValue()[i] == -std::numeric_limits<double>::infinity());
			}

			resetBoundaryConditions();
		}

		void distanceWithProjectionsInfiniteSpace()
		{
			Position firstPosition;
			Position secondPosition;
			firstPosition += randomVector();
			secondPosition += randomVector();
			Vector difference = firstPosition - secondPosition;
			auto [distance, projections] = firstPosition.distanceWithProjectionsTo(secondPosition);

			assert(equal(distance, difference.absoluteValue()));
			assert(equal(projections, difference));

			resetBoundaryConditions();
		}

		void distanceWithProjectionsPeriodicSpace()
		{
			double size = randomDouble<1, 10>();
			IDimensionsCondition* conditions[kDimensionalNumber];
			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i) {
				conditions[i] = new PeriodicDimension(size);
			}
			BoundaryConditions::setConditions(conditions);

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

		void normalizeInfiniteSpace()
		{
			Position initial = randomPosition();
			Position position = initial;
			position = position.normalize();
			assert(equal(initial, position));

			resetBoundaryConditions();
		}

		void normalizePeriodicSpace()
		{
			double size = randomDouble<1, 10>();
			IDimensionsCondition* conditions[kDimensionalNumber];
			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i) {
				conditions[i] = new PeriodicDimension(size);
			}
			BoundaryConditions::setConditions(conditions);

			Position initial = randomPosition<20, 30>();
			Position position = initial;
			position = position.normalize();
			for (std::uint8_t i = 0; i < kDimensionalNumber; ++i)
			{
				assert(!equal(initial[i], position[i]));
			}

			resetBoundaryConditions();
		}
	}

	namespace operators
	{
		void offsets()
		{
			Position initial = randomPosition();
			Position position = initial;
			assert(equal(position, initial));

			Vector offset = randomVector();
			position += offset;
			assert(!equal(position, initial));

			position -= offset;
			assert(equal(position, initial));
		}

		void binaryOffsets()
		{
			Position initial = randomPosition();
			Vector offset = randomVector();

			Position result = initial + offset;
			assert(!equal(result, initial));

			result = result - offset;
			assert(equal(result, initial));
		}

		void difference()
		{
			Position first = randomPosition();
			Vector offset = randomVector();
			Position second = first + offset;

			assert(equal(second - first, offset));
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

	testPositionClass::boundaryConditions::spaceSize();
	testPositionClass::boundaryConditions::infiniteSpace();
	testPositionClass::boundaryConditions::distanceWithProjectionsInfiniteSpace();
	testPositionClass::boundaryConditions::distanceWithProjectionsPeriodicSpace();
	testPositionClass::boundaryConditions::normalizeInfiniteSpace();
	testPositionClass::boundaryConditions::normalizePeriodicSpace();

	testPositionClass::operators::offsets();
	testPositionClass::operators::binaryOffsets();
	testPositionClass::operators::difference();
}
