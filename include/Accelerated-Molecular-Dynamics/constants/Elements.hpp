#pragma once
#ifndef TAHD_ELEMENTS_H
#define TAHD_ELEMENTS_H

#include <stdexcept>
#include <string>
#include <set>

namespace md
{
	class ElementException : public std::runtime_error {
	public:
		ElementException(const std::string& _Massage);
	};

	#define ENUM_CREATE
	#include "Elements helper/elements_enum.hpp"
	#undef ENUM_CREATE

	//functions throw ElementException if dont know values for this element
	// or element of enum does not have enumerator, that corresponding to title
	std::string to_string(const element e);
	element parse(const std::string& title);
	element parse(const char title);
	element parse(const char title[2]);
	/*get_atomic_mass functions return weightMean mass if isWeightedMean is true
	else return mass of random isotope given their prevalence in nature.
	During calculations, data from the files that placement folder Elements/Isotopes is used.
	In these files, the first column corresponds to the atomic weight, and the second to the 0 < prevalence <= 1*/
	int get_atomic_mass(const element e, const bool isWeightedMean = true);
	int get_atomic_mass(const char title, const bool isWeightedMean = true);
	int get_atomic_mass(const char title[2], const bool isWeightedMean = true);
	int get_atomic_mass(const std::string& title, const bool isWeightedMean = true);
	int get_atomic_number(const element el);
	int get_atomic_number(const char title);
	int get_atomic_number(const char title[2]);
	int get_atomic_number(const std::string& title);
	std::set<element> get_all();
}

#endif	// TAHD_ELEMENTS_H
