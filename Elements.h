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

element convert_to_element(char title);

element convert_to_element(char title[2]);

element convert_to_element(std::string title);

int get_atomic_mass(element el);

int get_atomic_mass(char title);

int get_atomic_mass(char title[2]);

int get_atomic_mass(std::string title);

int get_atomic_number(element el);

int get_atomic_number(char title);

int get_atomic_number(char title[2]);

int get_atomic_number(std::string title);

#endif	//TAHD_ELEMENTS_H
