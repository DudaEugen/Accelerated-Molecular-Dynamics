#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include <string>
#include <stdexcept>

enum class element {
	C  = 6,
	Al = 13,
	Si = 14,
	Ar = 18,
	Ti = 22,
	Fe = 26,
	Ni = 28,
	Cu = 29,
	Ag = 47,
	Au = 79
};

class ElementException : public std::runtime_error {
public:
	ElementException(const char _Massage);
	ElementException(const char _Massage[2]);
	ElementException(const std::string& _Massage);
private:
	const std::string massage();
};

element convert_to_element(const char title);

element convert_to_element(const char title[2]);

element convert_to_element(const std::string title);

int get_atomic_mass(const element el);

int get_atomic_mass(const char title);

int get_atomic_mass(const char title[2]);

int get_atomic_mass(const std::string title);

int get_atomic_number(const element el);

int get_atomic_number(const char title);

int get_atomic_number(const char title[2]);

int get_atomic_number(const std::string title);

#endif	//TAHD_ELEMENTS_H
