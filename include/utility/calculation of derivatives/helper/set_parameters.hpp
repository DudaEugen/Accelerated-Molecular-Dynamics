#pragma once
#ifndef TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T
#define TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T

#include <vector>
#include "structures.hpp"
#include "functions_folding.hpp"

namespace utils::fcd
{
    template<std::uint8_t Index>
    implementation::Constanta setParameters(const Parameter<Index> func, const std::vector<double>& params)
    {
        return implementation::Constanta(params[Index]);
    }

    template<class T>
    auto setParameters(const T& func, const std::vector<double>& params)
    {
        using namespace implementation;

        if constexpr (!T::IsFunction)
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

    template<std::uint8_t I, std::uint8_t Index>
    auto setParameterAsVariable(const Parameter<Index> func)
    {
        if constexpr (I == Index)
            return Variable();
        else
            return func;
    }

    template<std::uint8_t Index, class T>
    auto setParameterAsVariable(const T& func)
    {
        using namespace implementation;

        if constexpr (!T::IsFunction)
        {
            return func;
        }
        else if constexpr (T::IsContainParameter)
        {
            if constexpr (T::Type == FunctionType::OneArgument || 
                          T::Type == FunctionType::IndexedOneArgument)
            {
                return Function<
                    T::Name, 
                    decltype(setParameterAsVariable(func.argument)),
                    UnusedArgument,
                    T::TemplateIndex
                >{setParameterAsVariable(func.argument)};
            }
            else if constexpr (T::Type == FunctionType::TwoArgument)
            {
                return Function<
                    T::Name, 
                    decltype(setParameterAsVariable(func.argument1)), 
                    decltype(setParameterAsVariable(func.argument2)),
                    UnusedParameter
                >{setParameterAsVariable(func.argument1), setParameterAsVariable(func.argument2)};
            }
        }
        else
        {
            return func;
        }
        
    }
}

#endif  // TAHD_FUNCTIONS_FOR_DERIVATIVE_SET_PARAMETERS_T
