#include <algorithm>
#include <cmath>
#include "../tests.hpp"
#include "BoundaryConditions/DimensionsCondition/InfiniteDimension.hpp"
#include "BoundaryConditions/DimensionsCondition/PeriodicDimension.hpp"

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
            }

            void smallSize()
            {
                double firstRandom = randomDouble<1, 10>();
                double secondDouble = randomDouble<1, 10>();
                auto [normalized, size] = std::minmax(firstRandom, secondDouble);
                double unnormalized = std::floor(randomDouble<1, 10>()) * size + normalized;
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(normalized, condition->normalizeProjection(unnormalized)));
            }

            void negativeProjection()
            {
                double projection = randomDouble<-2, -1>();
                double size = randomDouble<3, 10>();
                double normalized = size - std::abs(projection);
                projection = std::round(randomDouble<-10, -1>()) * size + projection;
                IDimensionsCondition* condition = new PeriodicDimension(size);

                assert(equal(normalized, condition->normalizeProjection(projection)));
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
            }
        }
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
}
