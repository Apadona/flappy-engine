#include <engine_pch.hpp>

#include "math_exception.hpp"

template<std::uint8_t _row, std::uint8_t _colomn, typename U>
std::ostream& operator<<( std::ostream& out, const Matrix<_row,_colomn,U>& matrix )
{
    for( int i = 0; i < _row; ++i )
    {
        for( int j = 0; j < _colomn; ++j )
            out << matrix.m_data[i][j] << ' ';

        out << std::endl;
    }

    return out;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>::Matrix()
{
    CheckRowAndColomn();

    SetIdentity();  
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>::Matrix( const std::initializer_list<T>& _list )
{
    CheckRowAndColomn();
    
    SetData(_list.begin());
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>::Matrix( const Matrix<row,colomn,T>& other )
{
    CheckRowAndColomn();

    SetData(other.GetData());
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
constexpr bool Matrix<row,colomn,T>::IsSquare() const
{
    return row == colomn;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
constexpr bool Matrix<row,colomn,T>::HasDeterminant() const
{
    return IsSquare();
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
constexpr bool Matrix<row,colomn,T>::IsInverseable() const
{
    return HasDeterminant() && Determinant();
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
std::optional<T> Matrix<row,colomn,T>::Determinant() const
{
    if constexpr( !HasDeterminant() )
    {
        CORE_LOG_ERROR("Cannot calculate determinant on the matrix with rows of ",
                        row, " and colomns of ",colomn);
        return {};
    }

    std::optional<T> value;

    return value;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::Tranverse() const
{
    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            std::swap(m_data[i][j],m_data[j][i]);
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::Inverse() const
{
    if( !HasDeterminant() )
    {
        CORE_LOG_SOURCE(LogLevel::DEBUG);
        throw MathException(MATRIX_CANT_BE_REVERSED);
    }

    Matrix<row,colomn,T> mat;

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::SetIdentity()
{
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] = 0;

    if( HasDeterminant() ) // in other words, is it a square matrix?
        for( int i = 0; i < row; ++i )
            m_data[i][i] = 1;

    return *this;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator=( const ThisType& other )
{
    if( this == &other )
        return *this;

    SetData(other.GetData());

    return *this;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator=( const std::initializer_list<T>& _list )
{
    SetData(_list.begin());

    return *this;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
bool Matrix<row,colomn,T>::operator==( const ThisType& other )
{
    if( this == &other )
        return true;

    bool equal = true;

    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            if( m_data[i][j] != other.m_data[i][j] )
            {
                equal = false;
                break;
            }

    return equal;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
const T& Matrix<row,colomn,T>::operator[]( std::uint8_t index ) const
{
    auto division = index / colomn;
    auto remain = index % colomn;
    return m_data[division][remain];
} 

template<std::uint8_t row, std::uint8_t colomn, typename T>
T& Matrix<row,colomn,T>::operator[]( std::uint8_t index )
{
    auto division = index / colomn;
    auto remain = index % colomn;
    return m_data[division][remain];
}   

template<std::uint8_t row, std::uint8_t colomn, typename T>
void Matrix<row,colomn,T>::SetData( const T* data )
{
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] = data[i * row + j];
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
void Matrix<row,colomn,T>::CheckRowAndColomn() const
{
    static_assert( row >= 2 && colomn >= 2, "rows or colomns must be greater than 1!\n" );
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator+( T numeric ) const
{
    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            mat.m_data[i][j] = m_data[i][j] + numeric;

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator-( T numeric ) const
{
    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            mat.m_data[i][j] = m_data[i][j] - numeric;

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator*( T numeric ) const
{
    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            mat.m_data[i][j] = m_data[i][j] * numeric;

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator/( T numeric ) const
{
    if( numeric == 0 )
    {
        CORE_LOG_SOURCE(LogLevel::DEBUG);
        throw MathException(DIVIDE_BY_ZERO);
    }

    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            mat.m_data[i][j] = m_data[i][j] / numeric;

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator+=( T numeric )
{
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] += numeric;

    return *this;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator-=( T numeric )
{
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] -= numeric;

    return *this;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator*=( T numeric )
{
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] *= numeric;

    return *this;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator/=( T numeric )
{
    if( numeric == 0 )
    {
        CORE_LOG_SOURCE(LogLevel::DEBUG);
        throw MathException(DIVIDE_BY_ZERO);
    }

    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] /= numeric;

    return *this;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator+( const Matrix<row,colomn,T>& other ) const
{
    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            mat.m_data[i][j] = m_data[i][j] + other.m_data[i][j];

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator-( const Matrix<row,colomn,T>& other ) const
{
    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            mat.m_data[i][j] = m_data[i][j] - other.m_data[i][j];

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator*( const Matrix<row,colomn,T>& other ) const
{
    if( !( colomn == other.RowCount() ) )
    {
        CORE_LOG_SOURCE(LogLevel::DEBUG);
        throw MathException(MATRIX_CANT_MULTIPLY);
    }

    Matrix<row,colomn,T> mat;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
        {
            T sum = 0;

            for( int k = 0; k < colomn; ++k )
                sum += m_data[i][k] * other.m_data[k][j];

            mat.m_data[i][j] = sum;
        }

    return mat;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T> Matrix<row,colomn,T>::operator/( const Matrix<row,colomn,T>& other ) const
{
    return *this * Inverse(other);
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator+=( const Matrix<row,colomn,T>& other )
{
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] += other.m_data[i][j];
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator-=( const Matrix<row,colomn,T>& other )
{
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < colomn; ++j )
            m_data[i][j] -= other.m_data[i][j];
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator*=( const Matrix<row,colomn,T>& other )
{
    *this = *this * other;
}

template<std::uint8_t row, std::uint8_t colomn, typename T>
Matrix<row,colomn,T>& Matrix<row,colomn,T>::operator/=( const Matrix<row,colomn,T>& other )
{
    *this = *this * Inverse(other);
}