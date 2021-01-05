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
        else if constexpr (!is_function_fcd<T>)
        {
            return func;
        }
        else if constexpr (is_contain_parameter<T>)
        {
            if constexpr (is_one_argument_function<T>)
            {
                return const_function_folding(OneArgumentFunction<
                    T::function_t, decltype(set_parameters(func.argument, params))
                >{set_parameters(func.argument, params)});
            }
            else if constexpr (is_one_argument_int_template_par_function<T>)
            {
                return const_function_folding(OneArgumentIntTemplateParFunction<
                    T::function_t, decltype(set_parameters(func.argument, params)), T::template_index
                >{set_parameters(func.argument, params)});
            }
            else if constexpr (is_two_argument_function<T> )
            {
                return const_function_folding(TwoArgumentFunction<
                    T::function_t, 
                    decltype(set_parameters(func.argument1, params)), 
                    decltype(set_parameters(func.argument2, params))
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
