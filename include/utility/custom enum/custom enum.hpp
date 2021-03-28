#pragma once
#ifndef TAHD_CUSTOM_ENUM_H
#define TAHD_CUSTOM_ENUM_H

#include "macro functions.hpp"
#include <string>
#include <stdexcept>
#include <array>

// custom enum arguments
#define ARG_0_FUNCTION_HEADERS(x0, ...) x0
#define ARG_1_FUNCTION_HEADERS(x0, x1, ...) x1
#define ARG_2_FUNCTION_HEADERS(x0, x1, x2, ...) x2
#define ENUM_VALUE_VALUE_TUPLE(x0, ...) x0
#define ARG_0_VALUE_TUPLE(x0, ...)  ENUM_MACRO_PAIR(x0, #x0)
#define ARG_1_VALUE_TUPLE(x0, x1, ...) ENUM_MACRO_PAIR(x0, x1)
#define ARG_2_VALUE_TUPLE(x0, x1, x2, ...) ENUM_MACRO_PAIR(x0, x2)
#define ARG_3_VALUE_TUPLE(x0, x1, x2, x3, ...) ENUM_MACRO_PAIR(x0, x3)
#define ARG_0_ENUM_MACRO_PAIR(arg0, arg1) arg0
#define ARG_1_ENUM_MACRO_PAIR(arg0, arg1) arg1
#define ADD_PREF(pref, macro) pref##macro

// functions for custom enum

/* switch */
#define CASE_RETURN(enum_name, arg) case enum_name::ARG_0_##arg:                                 \
    return ARG_1_##arg;
#define ENUM_SWITH(arg, enum_name, ...) switch (arg)                                             \
    {                                                                                            \
        MACRO_FOREACH(CASE_RETURN, enum_name, NO_SEP, MACRO_ARGUMENTS(__VA_ARGS__))              \
    }                                                                                            \
    throw std::runtime_error(std::string("Incorrect value of custom enum: ") + #enum_name);     

/* to string */
#define ENUM_TO_STRING_SIGN(enum_name) std::string enum_name##_to_string(enum_name arg)    
#define ENUM_TO_STRING(enum_name, ...) ENUM_TO_STRING_SIGN(enum_name)                            \
    {                                                                                            \
        ENUM_SWITH(arg, enum_name, __VA_ARGS__)                                                  \
    }
 
/* enum functions */
#define ENUM_FUNCTION_SIGN(enum_name, f_header) f_header (enum_name arg) 
#define ENUM_FUNCTION_CREATOR(enum_name, f_header, ...) ENUM_FUNCTION_SIGN(enum_name, f_header)  \
    {                                                                                            \
        ENUM_SWITH(arg, enum_name, __VA_ARGS__)                                                  \
    }

/* custom enum create. N in FN is count of additional functions for enum
EXAMPLE: CREATE_ENUM_F3(
    enum_name,
    FUNCTION_HEADERS(int first_function_name, double second_function_name, int third_function_name),
    VALUE_TUPLE(FIRST_VALUE, 1, 1.0, 47),
    VALUE_TUPLE(SECOND_VALUE, 2, 2.0, -5),
    ...
)
MAX number of enum values is 255
MIN number of enum values is 1
<enum name>_impl namespace contain constexpr kMaxEnumValue value. Enum size equal kMaxEnumValue + 1
Values of enum is all std:int8_t numbers from 0 to kMaxEnumValue
*/
#define CUSTOM_ENUM_CREATE(name, ...) enum class name: std::uint8_t                              \
        {                                                                                        \
            MACRO_FOREACH(ADD_PREF, ENUM_VALUE_, KOMA_SEP, MACRO_ARGUMENTS(__VA_ARGS__))         \
        };                                                                                       \
        namespace name##_impl                                                                    \
        {                                                                                        \
            constexpr std::uint8_t kMaxEnumValue = MACRO_ARGS_SIZE(__VA_ARGS__) - 1;             \
            constexpr auto allEnumValues()                                                       \
            {                                                                                    \
                std::array<name, kMaxEnumValue+1> result{};                                      \
                for (std::uint8_t i = 0; i <= kMaxEnumValue; ++i)                                \
                    result[i] = name{i};                                                         \
                return result;                                                                   \
            }                                                                                    \
        }

#ifdef CPP_CUSTOM_ENUM
    #define CREATE_ENUM_F0(name, f_headers, ...) CUSTOM_ENUM_CREATE(name, __VA_ARGS__)           \
        ENUM_TO_STRING(name, MACRO_FOREACH(ADD_PREF, ARG_0_, KOMA_SEP, MACRO_ARGUMENTS(__VA_ARGS__)))

    #define CREATE_ENUM_F1(name, f_headers, ...) CREATE_ENUM_F0(name, f_headers, __VA_ARGS__)    \
        ENUM_FUNCTION_CREATOR(name, ARG_0_##f_headers,                                           \
                            MACRO_FOREACH(ADD_PREF, ARG_1_, KOMA_SEP, MACRO_ARGUMENTS(__VA_ARGS__)))

    #define CREATE_ENUM_F2(name, f_headers, ...) CREATE_ENUM_F1(name, f_headers, __VA_ARGS__)    \
        ENUM_FUNCTION_CREATOR(name, ARG_1_##f_headers,                                           \
                            MACRO_FOREACH(ADD_PREF, ARG_2_, KOMA_SEP, MACRO_ARGUMENTS(__VA_ARGS__)))

    #define CREATE_ENUM_F3(name, f_headers, ...) CREATE_ENUM_F2(name, f_headers, __VA_ARGS__)    \
        ENUM_FUNCTION_CREATOR(name, ARG_2_##f_headers,                                           \
                            MACRO_FOREACH(ADD_PREF, ARG_3_, KOMA_SEP, MACRO_ARGUMENTS(__VA_ARGS__)))
#else   // notdef CPP_CUSTOM_ENUM
    #define CREATE_ENUM_F0(name, f_headers, ...) CUSTOM_ENUM_CREATE(name, __VA_ARGS__)           \
        ENUM_TO_STRING_SIGN(name);                                                               

    #define CREATE_ENUM_F1(name, f_headers, ...) CREATE_ENUM_F0(name, f_headers, __VA_ARGS__)    \
        ENUM_FUNCTION_SIGN(name, ARG_0_##f_headers);

    #define CREATE_ENUM_F2(name, f_headers, ...) CREATE_ENUM_F1(name, f_headers, __VA_ARGS__)    \
        ENUM_FUNCTION_SIGN(name, ARG_1_##f_headers);

    #define CREATE_ENUM_F3(name, f_headers, ...) CREATE_ENUM_F2(name, f_headers, __VA_ARGS__)    \
        ENUM_FUNCTION_SIGN(name, ARG_2_##f_headers);
#endif  // CPP_CUSTOM_ENUM

#endif  // TAHD_CUSTOM_ENUM_H
