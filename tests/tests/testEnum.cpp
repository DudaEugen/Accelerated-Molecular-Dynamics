#include "../tests.hpp"
#include "custom enum/custom enum.hpp"
#include "iostream"

CREATE_ENUM_F2(
    elements,
    FUNCTION_HEADERS(std::uint8_t get_number, std::uint8_t get_mass),
    VALUE_TUPLE(H, 1, 1),
    VALUE_TUPLE(He, 2, 4),
    VALUE_TUPLE(Li, 3, 7),
    VALUE_TUPLE(Be, 4, 9),
    VALUE_TUPLE(B, 5, 11),
    VALUE_TUPLE(C, 6, 12),
    VALUE_TUPLE(O, 8, 16)
)

void testEnum()
{
    assert(MACRO_ARGS_SIZE(8) == 1);
    assert(MACRO_ARGS_SIZE(5, 6, 7, 0, 9) == 5);
    assert(MACRO_ARGS_SIZE(0, 1, 2, 3, 4, 6, 5, 7, 8, 0, 7) == 11);
    
    elements v = elements::H;
    assert(v == elements::H);
    assert(v != elements::He);
    assert(elements_to_string(v) == std::string{'H'});
    assert(get_number(v) == 1);
    assert(get_number(elements::B) == 5);
    assert(get_mass(v) == get_mass(elements::H));
    assert(get_mass(elements::O) == 16);
}
