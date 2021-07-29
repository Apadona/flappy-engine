#include "math_exception.hpp"

MathException::MathException( MathError error ) : m_error(error) {}

const char* MathException::what() const noexcept
{
    switch( m_error )
    {
        case DIVIDE_BY_ZERO:
            return "cannot divide by zero!\n";
    }       
}