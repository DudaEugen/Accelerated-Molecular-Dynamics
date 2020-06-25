#include "Elements.h"

#define GET_MASS
#include "Elements/elements_enum.h"
#include "Elements/macros_close.h"
#undef GET_MASS

#define CONVERT_TO_STRING
#include "Elements/elements_enum.h"
#include "Elements/macros_close.h"
#undef CONVERT_TO_STRING

#define PARSE_ELEMENT
#include "Elements/elements_enum.h"
#include "Elements/macros_close.h"
#undef PARSE_ELEMENT

#define ALL_ELEMENTS
#include "Elements/elements_enum.h"
#include "Elements/macros_close.h"
#undef ALL_ELEMENTS
#define TAHD_ELEMENT_ENUMERATION_MACROS

ElementException::ElementException(const std::string& _Massage) : std::runtime_error(_Massage)
{
}

element chem_element::parse(const char title)
{
	std::string elem = { title };
	return parse(elem);
}

element chem_element::parse(const char title[2])
{
	std::string elem = { title[0], title[1] };
	return parse(elem);
}

int chem_element::get_atomic_mass(const char title) { return get_atomic_mass(parse(title)); }

int chem_element::get_atomic_mass(const char title[2]) { return get_atomic_mass(parse(title)); }

int chem_element::get_atomic_mass(const std::string title) { return get_atomic_mass(parse(title)); }

int chem_element::get_atomic_number(const element el) { return static_cast<int>(el); }

int chem_element::get_atomic_number(const char title) { return static_cast<int>(parse(title)); }

int chem_element::get_atomic_number(const char title[2]) { return static_cast<int>(parse(title)); }

int chem_element::get_atomic_number(const std::string& title) { return static_cast<int>(parse(title)); }
