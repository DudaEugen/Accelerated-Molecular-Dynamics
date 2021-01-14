#include "../tests.hpp"
#include "System/BorderConditions.hpp"

using namespace md;

void testBorderConditionsDimensionalNumber3()
{
    if constexpr (DIMENSIONAL_NUMBER == 3)
	{
		std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bTypes = {
			BorderConditions::borderType::none,
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
		};
		BorderConditions bCond(Vector{0, 5, 11.2}, bTypes);
		Vector v; 
		Vector a;

		v = Vector{20, 20, 20};
		a = Vector{20, 0, -2.4};
		assert(not equal(bCond.computePosition(v), Vector{}));
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{-4.6, 0, 7.6}; 
		a = Vector{-4.6, 0, -3.6};	
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{0.01, -6, -12.7};
		a = Vector{0.01, -1, -1.5};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{1082, -56.7, 132.4}; 
		a = Vector{1082, -1.7, -2};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{0, -4.99, -11.2}; 
		a = Vector{0, 0.01, 0};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		v = Vector{0, 2, -5.5}; 
		a = Vector{0, 2, -5.5};
		assert(equal(bCond.computePosition(v), bCond.computePosition(a)));
		assert(equal(bCond(v), a.absoluteValue()));
		assert(equal(v, a));

		std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bTypes2 = {
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
		};
		BorderConditions bCond2(Vector{3, 4, 5}, bTypes2, Vector{-2, 3, 0});

		v = Vector{-1.9, -0.9, 0.1};
		a = Vector{1.1, 7.1, 5.1};	
		assert(not equal(v, a));
		assert(equal(bCond2.computePosition(v), bCond2.computePosition(a)));

		v = Vector{8, -9.6, -3};
		a = Vector{2, 2.4, 2};
		assert(equal(bCond2.computePosition(v), bCond2.computePosition(a)));
		assert(not equal(v, a));

		assert(equal(bCond.computePosition(Vector{}), Vector{}));
		assert(not equal(bCond2.computePosition(Vector{}), Vector{}));
		assert(equal(
            bCond.computePosition(Vector{0.5, 3.5, 2}), 
            bCond2.computePosition(Vector{0.5, 3.5, 2})
        ));
		assert(not equal(
            bCond.computePosition(Vector{4, 4, 4}), 
            bCond2.computePosition(Vector{4, 4, 4})
        ));
	}
}

void testBorderConditions()
{
    if constexpr (DIMENSIONAL_NUMBER == 3)
    {
        testBorderConditionsDimensionalNumber3();
    }
}
