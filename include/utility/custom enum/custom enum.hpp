#pragma once
#ifndef TAHD_CUSTOM_ENUM_H
#define TAHD_CUSTOM_ENUM_H

#include <string>
#include <stdexcept>

// macro functions
#define MACRO_ARGS_COUNT(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, res, ...) res
#define MACRO_ARGS_SIZE(...) MACRO_ARGS_COUNT(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9 , 8, 7, 6, 5, 4, 3, 2, 1)

#define MACRO_FOREACH_1(f, context, sep, arg) f(context, arg)
#define MACRO_FOREACH_2(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_1(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_3(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_2(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_4(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_3(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_5(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_4(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_6(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_5(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_7(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_6(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_8(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_7(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_9(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_8(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_10(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_9(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_11(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_10(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_12(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_11(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_13(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_12(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_14(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_13(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_15(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_14(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_16(f, context, sep, arg, ...) f(context, arg) ADD_##sep MACRO_FOREACH_15(f, context, sep, __VA_ARGS__)
#define MACRO_FOREACH_N(f, context, sep, count, ...) MACRO_FOREACH_##count(f, context, sep, __VA_ARGS__)
#define MACRO_ARGUMENTS(...) MACRO_ARGS_SIZE(__VA_ARGS__), __VA_ARGS__
#define MACRO_FOREACH(f, context, sep, ...) MACRO_FOREACH_N(f, context, sep, __VA_ARGS__)
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
        MACRO_FOREACH(CASE_RETURN, enum_name, NO_SEP, MACRO_ARGUMENTS(__VA_ARGS__))          \
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
        MACRO_FOREACH(ADD_PREF, ENUM_VALUE_, KOMA_SEP, MACRO_ARGUMENTS(__VA_ARGS__))         \
    };                                                                                       \
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

#endif  // TAHD_CUSTOM_ENUM_H
