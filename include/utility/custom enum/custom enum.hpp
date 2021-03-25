#pragma once
#ifndef TAHD_CUSTOM_ENUM_H
#define TAHD_CUSTOM_ENUM_H

#include <string>
#include <stdexcept>

// macro functions
#define ARGS_COUNT(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, res, ...) res
#define ARGS_SIZE(...) ARGS_COUNT(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9 , 8, 7, 6, 5, 4, 3, 2, 1)

#define FOREACH_1(macro, context, sep, arg) macro(context, arg)
#define FOREACH_2(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_1(macro, context, sep, __VA_ARGS__)
#define FOREACH_3(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_2(macro, context, sep, __VA_ARGS__)
#define FOREACH_4(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_3(macro, context, sep, __VA_ARGS__)
#define FOREACH_5(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_4(macro, context, sep, __VA_ARGS__)
#define FOREACH_6(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_5(macro, context, sep, __VA_ARGS__)
#define FOREACH_7(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_6(macro, context, sep, __VA_ARGS__)
#define FOREACH_8(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_7(macro, context, sep, __VA_ARGS__)
#define FOREACH_9(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_8(macro, context, sep, __VA_ARGS__)
#define FOREACH_10(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_9(macro, context, sep, __VA_ARGS__)
#define FOREACH_11(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_10(macro, context, sep, __VA_ARGS__)
#define FOREACH_12(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_11(macro, context, sep, __VA_ARGS__)
#define FOREACH_13(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_12(macro, context, sep, __VA_ARGS__)
#define FOREACH_14(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_13(macro, context, sep, __VA_ARGS__)
#define FOREACH_15(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_14(macro, context, sep, __VA_ARGS__)
#define FOREACH_16(macro, context, sep, arg, ...) macro(context, arg) ADD_##sep FOREACH_15(macro, context, sep, __VA_ARGS__)
#define FOREACH_N(macro, context, sep, count, ...) FOREACH_##count(macro, context, sep, __VA_ARGS__)
#define ARGUMENTS(...) ARGS_SIZE(__VA_ARGS__), __VA_ARGS__
#define FOREACH(macro, context, sep, ...) FOREACH_N(macro, context, sep, __VA_ARGS__)
#define ADD_KOMA_SEP ,
#define ADD_SEMICOLON_SEP ;
#define ADD_NO_SEP  

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
#define CASE_RETURN(enum_name, arg) case enum_name::ARG_0_##arg:                             \
    return ARG_1_##arg;
#define ENUM_SWITH(arg, enum_name, ...) switch (arg)                                                                                       \
    {                                                                                        \
        FOREACH(CASE_RETURN, enum_name, NO_SEP, ARGUMENTS(__VA_ARGS__))                      \
    }                                                                                        \
    throw std::runtime_error(std::string("Incorrect value of custom enum: ") + #enum_name);     

/* to string */
#define ENUM_TO_STRING(enum_name, ...) std::string enum_name##_to_string(enum_name arg)      \
    {                                                                                        \
        ENUM_SWITH(arg, enum_name, __VA_ARGS__)                                              \
    }
 
/* enum functions */
#define ENUM_FUNCTION_CREATOR(enum_name, f_header, ...) f_header (enum_name arg)             \
    {                                                                                        \
        ENUM_SWITH(arg, enum_name, __VA_ARGS__)                                              \
    }

/* custom enum create. N in FN is count of additional functions for enum
EXAMPLE: CREATE_ENUM_F3(
    enum_name,
    FUNCTION_HEADERS(int first_function_name, double second_function_name, int third_function_name),
    VALUE_TUPLE(FIRST_VALUE, 1, 1.0, 47),
    VALUE_TUPLE(SECOND_VALUE, 2, 2.0, -5),
    ...
)
*/
#define CREATE_ENUM_F0(name, f_headers, ...) enum class name                                 \
    {                                                                                        \
        FOREACH(ADD_PREF, ENUM_VALUE_, KOMA_SEP, ARGUMENTS(__VA_ARGS__))                     \
    };                                                                                       \
    ENUM_TO_STRING(name, FOREACH(ADD_PREF, ARG_0_, KOMA_SEP, ARGUMENTS(__VA_ARGS__)))

#define CREATE_ENUM_F1(name, f_headers, ...) CREATE_ENUM_F0(name, f_headers, __VA_ARGS__)    \
    ENUM_FUNCTION_CREATOR(name, ARG_0_##f_headers,                                           \
                          FOREACH(ADD_PREF, ARG_1_, KOMA_SEP, ARGUMENTS(__VA_ARGS__)))

#define CREATE_ENUM_F2(name, f_headers, ...) CREATE_ENUM_F1(name, f_headers, __VA_ARGS__)    \
    ENUM_FUNCTION_CREATOR(name, ARG_1_##f_headers,                                           \
                          FOREACH(ADD_PREF, ARG_2_, KOMA_SEP, ARGUMENTS(__VA_ARGS__)))

#define CREATE_ENUM_F3(name, f_headers, ...) CREATE_ENUM_F2(name, f_headers, __VA_ARGS__)    \
    ENUM_FUNCTION_CREATOR(name, ARG_2_##f_headers,                                           \
                          FOREACH(ADD_PREF, ARG_3_, KOMA_SEP, ARGUMENTS(__VA_ARGS__)))

#endif  // TAHD_CUSTOM_ENUM_H
