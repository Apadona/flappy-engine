#pragma once

#include "math_exception.hpp"

template<typename T>
struct Vector3D
{
    public:
        template<typename U>
        friend std::ostream& operator<<( std::ostream& out, const Vector3D<U>& _this );

        Vector3D() = default;
        Vector3D( T first, T second, T third );
        Vector3D( const Vector3D<T>& other );

        T Dot( const Vector3D<T>& other ) const;
        Vector3D<T> Cross( const Vector3D<T>& other ) const;
        T Length() const;
        Vector3D<T> Normal() const;

        Vector3D<T>& operator=( const Vector3D<T>& other );
        bool operator==( const Vector3D<T>& other ) const;
        
        Vector3D<T> operator+( const T& numeric ) const;
        Vector3D<T> operator-( const T& numeric ) const;
        Vector3D<T> operator*( const T& numeric ) const;
        Vector3D<T> operator/( const T& numeric ) const;

        Vector3D<T>& operator+=( const T& numeric );
        Vector3D<T>& operator-=( const T& numeric );
        Vector3D<T>& operator*=( const T& numeric );
        Vector3D<T>& operator/=( const T& numeric );

        Vector3D<T> operator+( const Vector3D<T>& other ) const;
        Vector3D<T> operator-( const Vector3D<T>& other ) const;
        Vector3D<T> operator*( const Vector3D<T>& other ) const;
        Vector3D<T> operator/( const Vector3D<T>& other ) const;

        Vector3D<T>& operator+=( const Vector3D<T>& other );
        Vector3D<T>& operator-=( const Vector3D<T>& other );
        Vector3D<T>& operator*=( const Vector3D<T>& other );
        Vector3D<T>& operator/=( const Vector3D<T>& other );

    public:
        union
        {
            struct
            {
                T a, b, c;
            };

            struct
            {
                T x, y, z;
            };

            struct
            {
                T u,v,t;
            };

            struct
            {
                T element[3];
            };
        };

};

using Vec3i = Vector3D<int>;
using Vec3l = Vector3D<long>;
using Vec3f = Vector3D<float>;
using Vec3d = Vector3D<double>;
using Vec3 = Vec3f;

#include "vector3D.inl"