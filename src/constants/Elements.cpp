#include "constants/Elements.hpp"
#include <random>
#include <ctime>
#include <fstream>

namespace md
{
	#define CONVERT_TO_STRING
	#include "constants/Elements helper/elements_enum.hpp"
	#include "constants/Elements helper/macros_close.hpp"
	#undef CONVERT_TO_STRING

	#define PARSE_ELEMENT
	#include "constants/Elements helper/elements_enum.hpp"
	#include "constants/Elements helper/macros_close.hpp"
	#undef PARSE_ELEMENT

	#define ALL_ELEMENTS
	#include "constants/Elements helper/elements_enum.hpp"
	#include "constants/Elements helper/macros_close.hpp"
	#undef ALL_ELEMENTS
	#define TAHD_ELEMENT_ENUMERATION_MACROS
}

md::ElementException::ElementException(const std::string& _Massage) : std::runtime_error(_Massage)
{
}

md::element md::parse(const char title) 
{ 
	std::string result;
	result += title;
	return parse(result);
}

md::element md::parse(const char title[2]) 
{ 
	std::string result;
	result += title[0];
	result += title[1];
	return parse(result);
}

int md::get_atomic_mass(const element e, const bool isWeightedMean)
{ 
	return get_atomic_mass(to_string(e), isWeightedMean);
}

int md::get_atomic_mass(const char title, const bool isWeightedMean)
{
	std::string result;
	result += title;
	return get_atomic_mass(result, isWeightedMean);
}

int md::get_atomic_mass(const char title[2], const bool isWeightedMean)
{
	std::string result;
	result += title[0];
	result += title[1];
	return get_atomic_mass(result, isWeightedMean);
}

int md::get_atomic_mass(const std::string& title, const bool isWeightedMean) 
{
	static bool isNeedSrand = true;

	std::ifstream file;
	file.open("src/constants/Elements helper/Isotopes/" + title);
	if (file.is_open())
	{
		if (isWeightedMean)
		{
			double val = 0;
			while (!file.eof())
			{
				int isotopeAtomicMass = 0;
				double isotopePrevalence = 0;
				file >> isotopeAtomicMass >> isotopePrevalence;
				val += isotopePrevalence * isotopeAtomicMass;
			}
			return std::round(val);
		}
		else
		{
			if (isNeedSrand)
			{
				srand(time(0));
				isNeedSrand = false;
			}
			double val = static_cast<double>(rand()) / RAND_MAX;
			double sum = 0;
			int isotopeAtomicMass = 0;
			double isotopePrevalence = 0;
			while (!file.eof())
			{
				file >> isotopeAtomicMass >> isotopePrevalence;
				sum += isotopePrevalence;
				if (val < isotopePrevalence)
					return isotopeAtomicMass;
			}
			return isotopeAtomicMass;
		}
	}
	throw(ElementException("Atomic mass of " + title + " don't know, because file in directory 'src/Elements/Isotopes' not found"));
}

int md::get_atomic_number(const element el) { return static_cast<int>(el); }

int md::get_atomic_number(const char title) { return get_atomic_number(parse(title)); }

int md::get_atomic_number(const char title[2]) { return get_atomic_number(parse(title)); }

int md::get_atomic_number(const std::string& title) { return get_atomic_number(parse(title)); }