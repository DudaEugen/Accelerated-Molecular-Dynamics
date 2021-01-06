#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T

#include <vector>
#include "structures.hpp"
#include "functions_folding.hpp"

namespace utils::fcd
{
    template<class T>
    auto set_parameters(const T& func, const std::vector<double>& params)
    {
        using namespace implementation;

        if constexpr (std::is_same_v<T, Parameter>)
        {
            return Constanta(params[func.index]);
        }
        else if constexpr (!T::is_function)
        {
            return func;
        }
        else if constexpr (T::is_contain_parameter)
        {
            if constexpr (T::type == function_type::ONE_ARGUMENT || 
                          T::type == function_type::INDEXED_ONE_ARGUMENT)
            {
                return const_function_folding(Function<
                    T::name, 
                    decltype(set_parameters(func.argument, params)),
                    UnusedArgument,
                    T::template_index
                >{set_parameters(func.argument, params)});
            }
            else if constexpr (T::type == function_type::TWO_ARGUMENT)
            {
                return const_function_folding(Function<
                    T::name, 
                    decltype(set_parameters(func.argument1, params)), 
                    decltype(set_parameters(func.argument2, params)),
                    UnusedParameter
                >{set_parameters(func.argument1, params), set_parameters(func.argument2, params)});
            }
        }
        else
        {
            return func;
        }
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T
