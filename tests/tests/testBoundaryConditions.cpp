#include <algorithm>
#include <cmath>
#include "tests.hpp"
#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"
#include "BoundaryConditions/DimensionsCondition/PeriodicDimension.hpp"
#include "BoundaryConditions/BoundaryConditions.hpp"

using namespace md;

namespace testDimensionsCondition
{ 
    namespace infinite
    {
        void test()
        {
            IDimensionsCondition* condition = new InfiniteDimension();
            double firstProjection = randomDouble();
            double secondProjection = randomDouble();

            assert(equal(firstProjection, condition->normalizeProjection(firstProjection)));
            assert(equal(secondProjection, condition->normalizeProjection(secondProjection)));
            assert(equal(
                secondProjection - firstProjection,
                condition->normalizeProjectionsDifference(secondProjection, firstProjection)
            ));
            assert(equal(
                firstProjection - secondProjection,
                condition->normalizeProjectionsDifference(firstProjection, secondProjection)
            ));

            delete condition;
        }
    }

    namespace periodic
    {
        namespace normalizeProjection
        {
            void bigSize()
            {
                double projection = randomDouble<1, 10>();
                double size = randomDouble<2, 10>() * projection;
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(projection, condition->normalizeProjection(projection)));

                delete condition;
            }

            void smallSize()
            {
                double firstRandom = randomDouble<1, 10>();
                double secondDouble = randomDouble<1, 10>();
                auto [normalized, size] = std::minmax(firstRandom, secondDouble);
                double unnormalized = std::floor(randomDouble<1, 10>()) * size + normalized;
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(normalized, condition->normalizeProjection(unnormalized)));

                delete condition;
            }

            void negativeProjection()
            {
                double projection = randomDouble<-2, -1>();
                double size = randomDouble<3, 10>();
                double normalized = size - std::abs(projection);
                projection = std::round(randomDouble<-10, -1>()) * size + projection;
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(normalized, condition->normalizeProjection(projection)));

                delete condition;
            }
        }

        namespace normalizeProjectionsDifference
        {
            void directly()
            {
                double firstProjection = randomDouble<1, 10>();
                double secondProjection = randomDouble<1, 10>();
                double size = randomDouble<2, 10>() * (firstProjection + secondProjection);
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(
                    secondProjection - firstProjection,
                    condition->normalizeProjectionsDifference(secondProjection, firstProjection)
                ));

                delete condition;
            }

            void throughBoundary()
            {
                double size = randomDouble<40, 50>();
                double firstProjection = randomDouble<1, 10>();
                double secondProjection = size - randomDouble<1, 10>();
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(
                    (secondProjection - firstProjection) - size,
                    condition->normalizeProjectionsDifference(secondProjection, firstProjection)
                ));

                delete condition;
            }

            void smallSize()
            {
                double size = randomDouble<2, 5>();
                double firstNormalized = randomDouble<0, 1>();
                double secondNormalized = randomDouble<0, 1>();
                double firstProjection = std::round(randomDouble<-10, 10>()) * size + firstNormalized;
                double secondProjection = std::round(randomDouble<-10, 10>()) * size + secondNormalized;
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(
                    secondNormalized - firstNormalized,
                    condition->normalizeProjectionsDifference(secondProjection, firstProjection)
                ));

                delete condition;
            }

            void smallSizeAndThroughBoundary()
            {
                double size = randomDouble<4, 10>();
                double firstNormalized = randomDouble<0, 1>();
                double secondNormalized = size - firstNormalized;
                double firstProjection = std::round(randomDouble<-10, 10>()) * size + firstNormalized;
                double secondProjection = std::round(randomDouble<-10, 10>()) * size + secondNormalized;
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(
                    (secondNormalized - firstNormalized) - size,
                    condition->normalizeProjectionsDifference(secondProjection, firstProjection)
                ));

                delete condition;
            }
        }
    }
}

namespace testBoundaryConditionsClass
{
    void infiniteSpace()
    {
        IDimensionsCondition* conditions[kDimensionalNumber];
        for (uint8_t i = 0; i < kDimensionalNumber; ++i) {
            conditions[i] = new InfiniteDimension();
        }
        BoundaryConditions::setConditions(conditions);
        Position firstPosition = randomPosition();
        Position secondPosition = randomPosition();

        assert(equal(firstPosition, BoundaryConditions::normolize(firstPosition)));
        assert(equal(secondPosition, BoundaryConditions::normolize(secondPosition)));
        assert(equal(
            (firstPosition - secondPosition).absoluteValue(),
            BoundaryConditions::distance(firstPosition, secondPosition)
        ));
        auto [distance, projections] = BoundaryConditions::distanceWithProjections(secondPosition, firstPosition);
        assert(equal((secondPosition - firstPosition).absoluteValue(), distance));
        assert(equal(secondPosition - firstPosition, projections));

        resetBoundaryConditions();
    }

    void randomConditions()
    {
        double size = randomDouble<1, 10>();
        IDimensionsCondition* conditions[kDimensionalNumber];
        for (uint8_t i = 0; i < kDimensionalNumber; ++i) {
            if (randomDouble<-1, 1>() > 0)
            {
                conditions[i] = new InfiniteDimension();
            } else {
                conditions[i] = new PeriodicDimension(size);
            }
        }
        BoundaryConditions::setConditions(conditions);
        Position firstPosition = randomPosition();
        Position secondPosition = randomPosition();

        Vector firstNormalize;
        for (uint8_t i = 0; i < kDimensionalNumber; ++i)
        {
            firstNormalize[i] = conditions[i]->normalizeProjection(firstPosition[i]);
        }
        Vector difference;
        for (uint8_t i = 0; i < kDimensionalNumber; ++i)
        {
            difference[i] = conditions[i]->normalizeProjectionsDifference(
                firstPosition[i], secondPosition[i]
            );
        }

        assert(equal(firstNormalize, BoundaryConditions::normolize(firstPosition)));
        assert(equal(difference.absoluteValue(), BoundaryConditions::distance(firstPosition, secondPosition)));
        auto [_, projections] = BoundaryConditions::distanceWithProjections(firstPosition, secondPosition);
        assert(equal(difference, projections));

        resetBoundaryConditions();
    }
}

void testBoundaryConditions()
{
    testDimensionsCondition::infinite::test();

    testDimensionsCondition::periodic::normalizeProjection::bigSize();
    testDimensionsCondition::periodic::normalizeProjection::smallSize();
    testDimensionsCondition::periodic::normalizeProjection::negativeProjection();
    testDimensionsCondition::periodic::normalizeProjectionsDifference::directly();
    testDimensionsCondition::periodic::normalizeProjectionsDifference::throughBoundary();
    testDimensionsCondition::periodic::normalizeProjectionsDifference::smallSize();
    testDimensionsCondition::periodic::normalizeProjectionsDifference::smallSizeAndThroughBoundary();

    testBoundaryConditionsClass::infiniteSpace();
    testBoundaryConditionsClass::randomConditions();
}
