#pragma once

template <typename Enumeration>
inline constexpr auto AsInteger(Enumeration const value) ->
                                typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}