#include "calculation of derivatives/helper/derivative_rules.hpp"

namespace impl = utils::fcd::implementation;

impl::ZeroConstanta impl::derivative_arg(impl::ZeroConstanta constanta) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta impl::derivative_arg(utils::fcd::Constanta constanta) noexcept
{
    return impl::ZeroConstanta();
}

impl::ZeroConstanta impl::derivative_arg(utils::fcd::Parameter parameter) noexcept
{
    return impl::ZeroConstanta();
}

utils::fcd::Constanta impl::derivative_arg(utils::fcd::Variable variable) noexcept
{
    return utils::fcd::Constanta(1);
}
