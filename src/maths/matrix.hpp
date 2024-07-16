#pragma once

#include <engine_pch.hpp>

#include <glm/gtc/type_ptr.hpp>

template<std::uint8_t row = 4, std::uint8_t colomn = 4, typename T = float>
class Matrix
{
    using ThisType = Matrix<row,colomn,T>;

    template<std::uint8_t _row, std::uint8_t _colomn, typename U>
    friend std::ostream& operator<<( std::ostream& out, const ThisType& matrix );

    public:
        Matrix();
        Matrix( const std::initializer_list<T>& _list );
        Matrix( const ThisType& other );

        const T* GetData() const { return &m_data[0][0]; }
        T* GetData() { return m_data; }

        constexpr std::uint8_t RowCount() const { return row; }
        constexpr std::uint8_t ColomnCount() const { return colomn; }
        constexpr std::uint16_t Length() const { return row * colomn; }
        
        constexpr std::size_t Size() const { return sizeof(m_data); }

        constexpr bool IsSquare() const;
        constexpr bool HasDeterminant() const;
        constexpr bool IsInverseable() const;

        std::optional<T> Determinant() const;
        ThisType Tranverse() const;
        ThisType Inverse() const;

        ThisType& SetIdentity();

        ThisType& operator=( const ThisType& other );
        ThisType& operator=( const std::initializer_list<T>& _list );

        T& operator[] ( std::uint8_t index );

        const T& operator[] ( std::uint8_t index ) const;

        bool operator==( const ThisType& other );

        ThisType operator+( T numeric ) const;
        ThisType operator-( T numeric ) const;
        ThisType operator*( T numeric ) const;
        ThisType operator/( T numeric ) const;

        ThisType& operator+=( T numeric );
        ThisType& operator-=( T numeric );
        ThisType& operator*=( T numeric );
        ThisType& operator/=( T numeric );

        ThisType operator+( const ThisType& other ) const;
        ThisType operator-( const ThisType& other ) const;
        ThisType operator*( const ThisType& other ) const;
        ThisType operator/( const ThisType& other ) const; // multiplies the matrix with the inverse of the other matrix.

        ThisType& operator+=( const ThisType& other );
        ThisType& operator-=( const ThisType& other );
        ThisType& operator*=( const ThisType& other );
        ThisType& operator/=( const ThisType& other ); // same thing as the above comment.

        void SetData( const T* data );

        void CheckRowAndColomn() const;

    public:
        T m_data[row][colomn];
};

#include "matrix.inl"

template<typename T>
using Mat2 = Matrix<2,2,T>;

using Mat2i = Matrix<2,2,int>;
using Mat2ui = Matrix<2,2,unsigned int>;
using Mat2f = Matrix<2,2,float>;
using Mat2d = Matrix<2,2,double>;

using Mat23i = Matrix<2,3,int>;
using Mat23ui = Matrix<2,3,unsigned int>;
using Mat23f = Matrix<2,3,float>;
using Mat23d = Matrix<2,3,double>;

using Mat24i = Matrix<2,4,int>;
using Mat24ui = Matrix<2,4,unsigned int>;
using Mat24f = Matrix<2,4,float>;
using Mat24d = Matrix<2,4,double>;

using Mat32i = Matrix<3,2,int>;
using Mat32ui = Matrix<3,2,unsigned int>;
using Mat32f = Matrix<3,2,float>;
using Mat32d = Matrix<3,2,double>;

template<typename T>
using Mat3 = Matrix<3,3,T>;

using Mat3i = Matrix<3,3,int>;
using Mat3ui = Matrix<3,3,unsigned int>;
using Mat3f = Matrix<3,3,float>;
using Mat3d = Matrix<3,3,double>;

using Mat34i = Matrix<3,4,int>;
using Mat34ui = Matrix<3,4,unsigned int>;
using Mat34f = Matrix<3,4,float>;
using Mat34d = Matrix<3,4,double>;

using Mat42i = Matrix<4,2,int>;
using Mat42ui = Matrix<4,2,unsigned int>;
using Mat42f = Matrix<4,2,float>;
using Mat42d = Matrix<4,2,double>;

using Mat43i = Matrix<4,3,int>;
using Mat43ui = Matrix<4,3,unsigned int>;
using Mat43f = Matrix<4,3,float>;
using Mat43d = Matrix<4,3,double>;

template<typename T>
using Mat4 = Matrix<4,4,T>;

using Mat44i = Matrix<4,4,int>;
using Mat44ui = Matrix<4,4,unsigned int>;
using Mat4f = Matrix<4,4,float>;
using Mat44d = Matrix<4,4,double>;
