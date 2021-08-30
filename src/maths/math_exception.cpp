#include "math_exception.hpp"

MathException::MathException( MathError error ) : m_error(error) {}

const char* MathException::what() const noexcept
{
    switch( m_error )
    {
        case DIVIDE_BY_ZERO:
            return "cannot divide by zero!\n";

        case VECTOR_ZERO_LENGTH_NORAML_CALCULATE:
            return "attempt to get a normal vector of a zero length vector!\n";

        case MATRIX_CANT_MULTIPLY:
            return "cannot multiply two matrixes where the colomn of the frist one isn't equal "
                   "to the row of the second one!\n";
        case MATRIX_CANT_BE_REVERSED:
            return "cannot reverse matrixes which aren't square and don't have determinants!\n";

        default:
            return "Math Error is not recongnized!\n";
    }       
}