#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include <string>
#include <stdexcept>

/*Everyone element is corresponding to number that equal to atomic number of this element. 
It is need change implementation of function get_atomic_number if previous statement not right.
When extending this enum is need add new enumerotors in implementation of convert_to_element and get_atomic_mass functions*/
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

//functions convert_to_element(title) throw ElementException if enum class element does not have enumerator, that corresponding to title
//or implementations of this functions dont known about this enumerator
element convert_to_element(const char title);

element convert_to_element(const char title[2]);

element convert_to_element(const std::string& title);

//function get_atomic_mass throw ElementException if enum class element does not have enumerator, that corresponding to argument
//or implementations of this functions dont known about this enumerator
int get_atomic_mass(const element el);

int get_atomic_mass(const char title);

int get_atomic_mass(const char title[2]);

int get_atomic_mass(const std::string title);

//function get_atomic_number throw ElementException if enum class element does not have enumerator, that corresponding to argument
int get_atomic_number(const element el);

int get_atomic_number(const char title);

int get_atomic_number(const char title[2]);

int get_atomic_number(const std::string& title);

#endif	//TAHD_ELEMENTS_H
