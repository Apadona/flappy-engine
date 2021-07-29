#pragma once

#include <exception>

enum MathError
{
    DIVIDE_BY_ZERO
};

class MathException : public std::exception
{
    public:
        MathException( MathError error );
        virtual const char* what() const noexcept;

    private:
        MathError m_error;
};