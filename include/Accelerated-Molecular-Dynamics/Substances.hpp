#pragma once
#ifndef TAHD_SUBSTANCES_H
#define TAHD_SUBSTANCES_H

#include <stdexcept>
#include "Elements.hpp"

enum class substance {
	Aluminum,
	Argon,
	Copper,
	Gold,
	Iron,
	Nickel,
	Silicon,
	Silver,
	Titanium,
	Zink,
	diamond,
	graphite,
};

class SubstanceException : public std::runtime_error {
public:
	SubstanceException(const std::string& _Massage);
private:
	const std::string massage();
};

substance convert_to_substance(const std::string& name);

double get_debye_temperature(const substance _substance);

#endif	//TAHD_SUBSTANCES_H
