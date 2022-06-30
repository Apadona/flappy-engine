#pragma once

#include <engine_pch.hpp>

enum MathError
{
    DIVIDE_BY_ZERO,
    VECTOR_ZERO_LENGTH_NORAML_CALCULATE,
    MATRIX_CANT_MULTIPLY,
    MATRIX_CANT_BE_REVERSED
};

class MathException : public std::exception
{
    public:
        MathException( MathError error );
        virtual const char* what() const noexcept;

    private:
        MathError m_error;
};