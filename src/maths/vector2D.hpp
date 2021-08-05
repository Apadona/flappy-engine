#pragma once

#include "vector2D.hpp"

#include "math_exception.hpp"

#include <iostream>
#include <cmath>

template<typename T>
struct Vector2D
{
    public:
        template<typename U>
        friend std::ostream& operator<<( std::ostream& out, const Vector2D<U>& _this );

        Vector2D() = default;
        Vector2D( T first, T second );
        Vector2D( const Vector2D<T>& other );
        
        T Dot( const Vector2D<T>& other ) const;
        T Length() const;

        Vector2D<T>& operator=( const Vector2D<T>& other );
        bool operator==( const Vector2D<T>& other ) const;
        
        Vector2D<T> operator+( const T& numeric ) const;
        Vector2D<T> operator-( const T& numeric ) const;
        Vector2D<T> operator*( const T& numeric ) const;
        Vector2D<T> operator/( const T& numeric ) const;

        Vector2D<T>& operator+=( const T& numeric );
        Vector2D<T>& operator-=( const T& numeric );
        Vector2D<T>& operator*=( const T& numeric );
        Vector2D<T>& operator/=( const T& numeric );

        Vector2D<T> operator+( const Vector2D<T>& other ) const;
        Vector2D<T> operator-( const Vector2D<T>& other ) const;
        Vector2D<T> operator*( const Vector2D<T>& other ) const;
        Vector2D<T> operator/( const Vector2D<T>& other ) const;

        Vector2D<T>& operator+=( const Vector2D<T>& other );
        Vector2D<T>& operator-=( const Vector2D<T>& other );
        Vector2D<T>& operator*=( const Vector2D<T>& other );
        Vector2D<T>& operator/=( const Vector2D<T>& other );

    public:
        union
        {
            struct
            {
                T a;
                T b;
            };

            struct
            {
                T x;
                T y;
            };

            struct
            {
                T u;
                T v;
            };
        };
};

using Vec2i = Vector2D<int>;
using Vec2l = Vector2D<long>;
using Vec2f = Vector2D<float>;
using Vec2d = Vector2D<double>;
using Vec2 = Vec2f;

#include "vector2D.inl"