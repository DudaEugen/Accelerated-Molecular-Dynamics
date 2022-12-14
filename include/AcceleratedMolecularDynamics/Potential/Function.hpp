#pragma once
#ifndef TAHD_BASE_FUNCTION_H
#define TAHD_BASE_FUNCTION_H

#include "CalculationOfDerivatives/Functions.hpp"

namespace md
{
    class IBaseFunction
    {
    public:
        virtual double function(double value) const = 0;
        virtual double derivative(double value) const = 0;
        virtual ~IBaseFunction() = 0;
    };

    template<class T>
    class Function: public IBaseFunction
    {
    private:
        using argType = decltype(utils::fcd::setParameters(std::declval<T>(), std::vector<double>()));
        argType func;

    public:
        Function(const T& function): func{ function }
        {
        }
        Function(const T& function, const std::vector<double>& params): 
            func{ utils::fcd::setParameters(function, params) }
        {
        }
        double function(double value) const override
        {
            return func(value);
        }
        double derivative(double value) const override
        {
            return utils::fcd::derivative(func)(value);
        }
    };

    inline constexpr auto P0 = utils::fcd::Parameter<0>();
    inline constexpr auto P1 = utils::fcd::Parameter<1>();
    inline constexpr auto P2 = utils::fcd::Parameter<2>();
    inline constexpr auto P3 = utils::fcd::Parameter<2>();
    inline constexpr auto P4 = utils::fcd::Parameter<2>();
    inline constexpr auto P5 = utils::fcd::Parameter<2>();
    inline constexpr auto P6 = utils::fcd::Parameter<2>();
    inline constexpr auto P7 = utils::fcd::Parameter<2>();
    inline constexpr auto P8 = utils::fcd::Parameter<2>();
    inline constexpr auto P9 = utils::fcd::Parameter<2>();
    inline constexpr auto P10 = utils::fcd::Parameter<2>();
    inline constexpr auto P11 = utils::fcd::Parameter<2>();
    inline constexpr auto X = utils::fcd::Variable();
}

#endif	//TAHD_BASE_FUNCTION_H
