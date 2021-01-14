#include "../tests.hpp"
#include "constants/Substances.hpp"

using namespace md;

void testSubstance()
{
    assert(convert_to_substance("aluminum") == substance::Aluminum);
	assert(convert_to_substance("AluminUm") == substance::Aluminum);
	assert(convert_to_substance("Graphite") == substance::graphite);
	assert(convert_to_substance("CoPPeR") == substance::Copper);
	assert(equal(get_debye_temperature(convert_to_substance("Aluminum")), 390));
	assert(equal(get_debye_temperature(substance::Gold), 178.));
}
