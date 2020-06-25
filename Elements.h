#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include <stdexcept>
#include <string>
#include <vector>

class ElementException : public std::runtime_error {
public:
	ElementException(const std::string& _Massage);
};

#define ENUM_CREATE
#include "Elements/elements_enum.h"
#undef ENUM_CREATE

namespace chem_element
{
	//functions throw ElementException if dont know values for this element
	// or element of enum does not have enumerator, that corresponding to title
	std::string to_string(const element e);
	element parse(const std::string& title);
	element parse(const char title);
	element parse(const char title[2]);
	int get_atomic_mass(const element e);
	int get_atomic_mass(const char title);
	int get_atomic_mass(const char title[2]);
	int get_atomic_mass(const std::string title);
	int get_atomic_number(const element el);
	int get_atomic_number(const char title);
	int get_atomic_number(const char title[2]);
	int get_atomic_number(const std::string& title);
	std::vector<element> get_all();
}

#endif	// TAHD_ELEMENTS_H
