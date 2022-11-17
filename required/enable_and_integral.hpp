#ifndef ENABLE_AND_INTEGRAL_HPP
#define ENABLE_AND_INTEGRAL_HPP

#include <limits>

namespace ft
{

    template<bool Cond, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> { typedef T type; };

    template <class T>
    struct is_integral;

    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T,v> type;
        
        operator T() const { return v; }
    };

    typedef integral_constant<bool, false> false_type;
    typedef integral_constant<bool, true> type_true;
    
    template<typename T> struct is_integral : false_type {};
    
    template<> struct is_integral<bool> : type_true {};
    
    template<> struct is_integral<char> : type_true {};
    
    template<> struct is_integral<char16_t> : type_true {};
    
    template<> struct is_integral<char32_t> : type_true {};
    
    template<> struct is_integral<wchar_t> : type_true {};
    
    template<> struct is_integral<signed char> : type_true {};
    
    template<> struct is_integral<short int> : type_true {};
    
    template<> struct is_integral<int> : type_true {};
    
    template<> struct is_integral<long int> : type_true {};
    
    template<> struct is_integral<long long int> : type_true {};
    
    template<> struct is_integral<unsigned char> : type_true {};
    
    template<> struct is_integral<unsigned short int> : type_true {};
    
    template<> struct is_integral<unsigned int> : type_true {};
    
    template<> struct is_integral<unsigned long int> : type_true {};
    
    template<> struct is_integral<unsigned long long int> : type_true {};
    
}

#endif