#include "constants/Substances.hpp"

md::SubstanceException::SubstanceException(const std::string& _Massage) 
	: std::runtime_error(massage() + _Massage)
{
}

const std::string md::SubstanceException::massage() { return "invalid or nondefined substance "; }

std::string convert_to_lover(const std::string& s)
{
	std::string result = "";
	for (char c : s)
	{
		result += tolower(c);
	}
	return result;
}

md::substance md::convert_to_substance(const std::string& name)
{
	if (convert_to_lover(name) == "aluminum") { return substance::Aluminum; }
	else if (convert_to_lover(name) == "argon") { return substance::Argon; }
	else if (convert_to_lover(name) == "copper") { return substance::Copper; }
	else if (convert_to_lover(name) == "gold") { return substance::Gold; }
	else if (convert_to_lover(name) == "iron") { return substance::Iron; }
	else if (convert_to_lover(name) == "nickel") { return substance::Nickel; }
	else if (convert_to_lover(name) == "silicon") { return substance::Silicon; }
	else if (convert_to_lover(name) == "silver") { return substance::Silver; }
	else if (convert_to_lover(name) == "titanium") { return substance::Titanium; }
	else if (convert_to_lover(name) == "zink") { return substance::Zink; }
	else if (convert_to_lover(name) == "diamond") { return substance::diamond; }
	else if (convert_to_lover(name) == "graphite") { return substance::graphite; }
	throw SubstanceException(name);
}

double md::get_debye_temperature(const substance _substance)
{
	double result = -1;
	switch (_substance)
	{
	case substance::Aluminum:
		result = 390;
		break;
	case substance::Argon:
		result = 92;
		break;
	case substance::Copper:
		result = 310;
		break;
	case substance::Gold:
		result = 178;
		break;
	case substance::Iron:
		result = 373;
		break;
	case substance::Nickel:
		result = 345;
		break;
	case substance::Silicon:
		result = 692;
		break;
	case substance::Silver:
		result = 221;
		break;
	case substance::Titanium:
		result = 380;
		break;
	case substance::Zink:
		result = 237;
		break;
	case substance::diamond:
		result = 2250;
		break;
	case substance::graphite:
		result = 413;
		break;
	}
	
	if (result > 0)
	{
		return result;
	}
	else
	{
		throw SubstanceException("Debye temperature");
	}
}
