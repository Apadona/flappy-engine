#include "lerp.hpp"
#include "helpers.hpp"

#include <utility>

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