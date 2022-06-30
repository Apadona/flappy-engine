#pragma once

#include "math_exception.hpp"

template<typename T>
struct Vector4D
{
    public:
        template<typename U>
        friend std::ostream& operator<<( std::ostream& out, const Vector4D<U>& _this );

        Vector4D() = default;
        Vector4D( T first, T second, T third , T forth );
        Vector4D( const Vector4D<T>& other );

        T Dot( const Vector4D<T>& other ) const;
        T Length() const;
        Vector4D<T> Normal() const;

        Vector4D<T>& operator=( const Vector4D<T>& other );
        bool operator==( const Vector4D<T>& other ) const;
        
        Vector4D<T> operator+( const T& numeric ) const;
        Vector4D<T> operator-( const T& numeric ) const;
        Vector4D<T> operator*( const T& numeric ) const;
        Vector4D<T> operator/( const T& numeric ) const;

        Vector4D<T>& operator+=( const T& numeric );
        Vector4D<T>& operator-=( const T& numeric );
        Vector4D<T>& operator*=( const T& numeric );
        Vector4D<T>& operator/=( const T& numeric );

        Vector4D<T> operator+( const Vector4D<T>& other ) const;
        Vector4D<T> operator-( const Vector4D<T>& other ) const;
        Vector4D<T> operator*( const Vector4D<T>& other ) const;
        Vector4D<T> operator/( const Vector4D<T>& other ) const;

        Vector4D<T>& operator+=( const Vector4D<T>& other );
        Vector4D<T>& operator-=( const Vector4D<T>& other );
        Vector4D<T>& operator*=( const Vector4D<T>& other );
        Vector4D<T>& operator/=( const Vector4D<T>& other );

    public:
        union
        {
            struct
            {
                T a, b, c, d;
            };

            struct
            {
                T x, y, z, w;
            };

            struct
            {
                T element[4];
            };
        };

};

using Vec4i = Vector4D<int>;
using Vec4l = Vector4D<long>;
using Vec4f = Vector4D<float>;
using Vec4d = Vector4D<double>;
using Vec4 = Vec4f;

#include "vector4D.inl"