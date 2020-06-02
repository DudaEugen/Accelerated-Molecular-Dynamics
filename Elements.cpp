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

element convert_to_element(const char title)
{
	if (title == 'C') { return element::C; }
	throw ElementException(title);
}

element convert_to_element(const char title[2])
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

element convert_to_element(const std::string& title)
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

int get_atomic_mass(const element el)
{
	int result = -1;
	switch (el)
	{
		case element::C:
			result = 12;
			break;
		case element::Al:
			result = 27;
			break;
		case element::Si:
			result = 28;
			break;
		case element::Ar:
			result = 40;
			break;
		case element::Ti:
			result = 48;
			break;
		case element::Fe:
			result = 56;
			break;
		case element::Ni:
			result = 59;
			break;
		case element::Cu:
			result = 64;
			break;
		case element::Ag:
			result = 108;
			break;
		case element::Au:
			result = 197;
			break;
	}

	if (result > 0)
	{
		return result;
	}
	else
	{
		throw ElementException(std::string("in function get_atomic_mass(element el)"));
	}
}

int get_atomic_mass(const char title)
{
	return get_atomic_mass(convert_to_element(title));
}

int get_atomic_mass(const char title[2])
{
	return get_atomic_mass(convert_to_element(title));
}

int get_atomic_mass(const std::string title)
{
	return get_atomic_mass(convert_to_element(title));
}

int get_atomic_number(const element el)
{
	return static_cast<int>(el);
}

int get_atomic_number(const char title)
{
	return get_atomic_number(convert_to_element(title));
}

int get_atomic_number(const char title[2])
{
	return get_atomic_number(convert_to_element(title));
}

int get_atomic_number(const std::string& title)
{
	return get_atomic_number(convert_to_element(title));
}
