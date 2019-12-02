#include "Elements.h"

ElementException::ElementException(const char _Massage)	: std::runtime_error(massage() + _Massage)
{
}

ElementException::ElementException(const char _Massage[2]) : std::runtime_error(massage() + _Massage[0] + _Massage[1])
{
}

ElementException::ElementException(const std::string& _Massage) : std::runtime_error(massage() + _Massage)
{
}

const std::string ElementException::massage() {	return "invalid or nondefined element "; }

element convert_to_element(char title)
{
	if (title == 'C') { return element::C; }
	throw ElementException(title);
}

element convert_to_element(char title[2])
{
	if (title[0] == 'A' && title[1] == 'l') { return element::Al; }
	else if (title[0] == 'S' && title[1] == 'i') { return element::Si; }
	else if (title[0] == 'A' && title[1] == 'r') { return element::Ar; }
	else if (title[0] == 'T' && title[1] == 'i') { return element::Ti; }
	else if (title[0] == 'F' && title[1] == 'e') { return element::Fe; }
	else if (title[0] == 'N' && title[1] == 'i') { return element::Ni; }
	else if (title[0] == 'C' && title[1] == 'u') { return element::Cu; }
	else if (title[0] == 'A' && title[1] == 'g') { return element::Ag; }
	else if (title[0] == 'A' && title[1] == 'u') { return element::Au; }
	throw ElementException(title);
}

element convert_to_element(std::string title)
{
	if (title == "C") { return element::C; }
	else if (title == "Al") { return element::Al; }
	else if (title == "Si") { return element::Si; }
	else if (title == "Ar") { return element::Ar; }
	else if (title == "Ti") { return element::Ti; }
	else if (title == "Fe") { return element::Fe; }
	else if (title == "Ni") { return element::Ni; }
	else if (title == "Cu") { return element::Cu; }
	else if (title == "Ag") { return element::Ag; }
	else if (title == "Au") { return element::Au; }
	throw ElementException(title);
}

int get_atomic_mass(element el)
{
	if (el == element::C) { return 12; }
	else if (el == element::Al) { return 27; }
	else if (el == element::Si) { return 28; }
	else if (el == element::Ar) { return 40; }
	else if (el == element::Ti) { return 48; }
	else if (el == element::Fe) { return 56; }
	else if (el == element::Ni) { return 59; }
	else if (el == element::Cu) { return 64; }
	else if (el == element::Ag) { return 108; }
	else if (el == element::Au) { return 197; }
	throw ElementException(std::string("in function get_atomic_mass(element el)"));
}

int get_atomic_mass(char title)
{
	return get_atomic_mass(convert_to_element(title));
}

int get_atomic_mass(char title[2])
{
	return get_atomic_mass(convert_to_element(title));
}

int get_atomic_mass(std::string title)
{
	return get_atomic_mass(convert_to_element(title));
}

int get_atomic_number(element el)
{
	return static_cast<int>(el);
}

int get_atomic_number(char title)
{
	return get_atomic_number(convert_to_element(title));
}

int get_atomic_number(char title[2])
{
	return get_atomic_number(convert_to_element(title));
}

int get_atomic_number(std::string title)
{
	return get_atomic_number(convert_to_element(title));
}
