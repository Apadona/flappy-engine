#include "lerp.hpp"

#include <utility>

namespace
{
    //TODO: must be implemented in some util file.
    template<typename T>
    std::pair<T,T> MinMax( T arg1, T arg2 )
    {
        T min,max;
        
        if( arg1 < arg2 )
        {
            min = arg1;
            max = arg2;
        }

        else
        {
            min = arg2;
            max = arg1;
        }

        return {min,max};
    }
}

Lerp::Lerp( float lower, float upper, float step ) : m_step(step)
{
   std::pair<float,float> _pair = MinMax(lower,upper);

    m_lower = _pair.first;
    m_upper = _pair.second;

    m_current_value = m_lower;
}

void Lerp::Update()
{
    m_current_value += m_step;

    if( m_current_value > m_upper )
    {
        m_step = -m_step;
        m_current_value = m_upper;
    }

    else if( m_current_value < m_lower )
    {
        m_step = -m_step;
        m_current_value = m_lower;
    }
}

void Lerp::Reset( float value )
{
    if( value > m_upper || value < m_lower )
    {
        m_current_value = m_lower;
        return;
    }

    m_current_value = value;
}