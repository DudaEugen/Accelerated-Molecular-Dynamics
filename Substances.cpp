#include "Substances.h"

SubstanceException::SubstanceException(const std::string& _Massage) : std::runtime_error(massage() + _Massage)
{
}

const std::string SubstanceException::massage() { return "invalid or nondefined substance "; }
