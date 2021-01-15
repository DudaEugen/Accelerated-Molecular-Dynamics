#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T

#include <vector>
#include "structures.hpp"
#include "functions_folding.hpp"

namespace utils::fcd
{
    template<class T>
    auto setParameters(const T& func, const std::vector<double>& params)
    {
        using namespace implementation;

        if constexpr (std::is_same_v<T, Parameter>)
        {
            return Constanta(params[func.index]);
        }
        else if constexpr (!T::IsFunction)
        {
            return func;
        }
        else if constexpr (T::IsContainParameter)
        {
            if constexpr (T::Type == FunctionType::OneArgument || 
                          T::Type == FunctionType::IndexedOneArgument)
            {
                return constFunctionFolding(Function<
                    T::Name, 
                    decltype(setParameters(func.argument, params)),
                    UnusedArgument,
                    T::TemplateIndex
                >{setParameters(func.argument, params)});
            }
            else if constexpr (T::Type == FunctionType::TwoArgument)
            {
                return constFunctionFolding(Function<
                    T::Name, 
                    decltype(setParameters(func.argument1, params)), 
                    decltype(setParameters(func.argument2, params)),
                    UnusedParameter
                >{setParameters(func.argument1, params), setParameters(func.argument2, params)});
            }
        }
        else
        {
            return func;
        }
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T
