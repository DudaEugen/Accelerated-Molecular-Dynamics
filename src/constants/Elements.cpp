#define CPP_CUSTOM_ENUM
#include "constants/Elements.hpp"

md::ElementException::ElementException(const std::string& _Massage) : std::runtime_error(_Massage)
{
}

md::element md::parse(const std::string& title)
{
    for (element el: element_impl::allEnumValues())
        if(element_to_string(el) == title)
            return el;
    throw ElementException(std::string("Can't parse to element string: ") + title);
}

md::element md::parse(char title)
{
	return parse(std::string{title});
}

md::element md::parse(const char title[2])
{
    return parse(std::string{title, 2});
}

unsigned md::get_atomic_mass(char title)
{
    return get_atomic_mass(parse(title));
}

unsigned md::get_atomic_mass(const char title[2])
{
    return get_atomic_mass(parse(title));
}

unsigned md::get_atomic_mass(const std::string& title)
{
    return get_atomic_mass(parse(title));
}

std::uint8_t md::get_atomic_number(char title)
{
    return get_atomic_number(title);
}

std::uint8_t md::get_atomic_number(const char title[2])
{
    return get_atomic_number(title);
}

std::uint8_t md::get_atomic_number(const std::string& title)
{
    return get_atomic_number(title);
}
