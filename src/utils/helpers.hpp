#pragma once

#include <utility>
#include <type_traits>

template <typename Enumeration>
inline constexpr auto AsInteger(Enumeration const value) ->
                                typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template<typename T>
inline constexpr std::pair<T,T> MinMax( const T& first, const T& second )
{
    if( first > second )
        return std::pair<T,T>(second,first);

    return std::pair<T,T>(first,second);    
}

template<typename T>
inline constexpr bool IsFloatingValue()
{
    return std::is_same<float,T>::value || std::is_same<double,T>::value || 
           std::is_same<long double,T>::value;
}