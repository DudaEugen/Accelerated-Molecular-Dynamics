#include "Substances.h"

SubstanceException::SubstanceException(const std::string& _Massage) : std::runtime_error(massage() + _Massage)
{
}

const std::string SubstanceException::massage() { return "invalid or nondefined substance "; }

substance convert_to_substance(const std::string& name)
{
	if (name == "Aluminum") { return substance::Aluminum; }
	else if (name == "Argon") { return substance::Argon; }
	else if (name == "Copper") { return substance::Copper; }
	else if (name == "Gold") { return substance::Gold; }
	else if (name == "Iron") { return substance::Iron; }
	else if (name == "Nickel") { return substance::Nickel; }
	else if (name == "Silicon") { return substance::Silicon; }
	else if (name == "Silver") { return substance::Silver; }
	else if (name == "Titanium") { return substance::Titanium; }
	else if (name == "Zink") { return substance::Zink; }
	else if (name == "diamond") { return substance::diamond; }
	else if (name == "graphite") { return substance::graphite; }
	throw SubstanceException(name);
}

double get_debye_temperature(const substance _substance)
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
