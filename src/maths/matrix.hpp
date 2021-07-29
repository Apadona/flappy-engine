/*
#pragma once

#include <iostream>
#include <initializer_list>
#include <cstdint>

template<typename T, std::uint8_t row, std::uint8_t colomn>
class Matrix
{
    using ThisType = Matrix<T,row,colomn>;

    friend ostream& operator<<( ostream& out, const ThisType& matrix );

    public:
        Matrix() = default;
        Matrix( std::initializer_list<T> _list );
        Matrix( const ThisType& other );

        const T* GetData() const { return m_data; }
        T* GetData() { return m_data; }

        std::uint8_t RowCount() const { return row; }
        std::uint8_t ColomnCount() const { return colomn; }
        std::uint16_t Length() const { return row * colomn; }
        
        std::size_t Size() const { return sizeof(m_data); }

        ThisType& Tranverse();
        ThisType& Inverse();
        T Determinant();

        ThisType& operator=( const ThisType& other );
        ThisType& operator=( const std::initializer_list<T>& _list );

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
        ThisType operator/=( const ThisType& other ) const;

        ThisType& operator+=( const ThisType& other );
        ThisType& operator-=( const ThisType& other );
        ThisType& operator*=( const ThisType& other );
        ThisType& operator/=( const ThisType& other );

        bool CanHaveDeterninant();
        bool CanBeInverseable();

        private:
            void SetData( const T* data, const std::size_t size );

    public:
        //std::array<T,row * colomn> m_data;
        T m_data[ row * colomn ];
};*/