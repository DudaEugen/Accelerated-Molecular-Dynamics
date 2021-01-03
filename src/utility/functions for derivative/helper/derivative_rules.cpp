#include "utility/functions for derivative/helper/derivative_rules.hpp"

Constanta derivative_const(Constanta constanta) noexcept
{
    return Constanta(0);
}

Constanta derivative_param(Parameter parameter) noexcept
{
    return Constanta(0);
}

Constanta derivative_var(Variable variable) noexcept
{
    return Constanta(1);
}
