#include "functions for derivative/helper/derivative_rules.hpp"

ZeroConstanta derivative_arg(ZeroConstanta constanta) noexcept
{
    return ZeroConstanta();
}

ZeroConstanta derivative_arg(Constanta constanta) noexcept
{
    return ZeroConstanta();
}

ZeroConstanta derivative_arg(Parameter parameter) noexcept
{
    return ZeroConstanta();
}

Constanta derivative_arg(Variable variable) noexcept
{
    return Constanta(1);
}
