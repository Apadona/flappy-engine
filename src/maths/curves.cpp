#include "curves.hpp"

BezierCurve::BezierCurve( const BezierCurve& other )
{
    *this = other;
}

BezierCurve::BezierCurve( BezierCurve&& other )
{
    *this = std::forward<BezierCurve>(other);
}

BezierCurve::BezierCurve( const ControlPoints& cp )
{
    *this = cp;
}

BezierCurve::BezierCurve( ControlPoints&& cp )
{
    *this = std::forward<ControlPoints>(cp);
}

BezierCurve& BezierCurve::operator=( const BezierCurve& other )
{
    if( this != &other )
        m_cp = other.m_cp;
}

BezierCurve& BezierCurve::operator=( BezierCurve&& other )
{
    if( this != &other )
        m_cp = std::move(other.m_cp);

}

BezierCurve& BezierCurve::operator=( const ControlPoints& cp )
{
    m_cp = cp;
}

BezierCurve& BezierCurve::operator=( ControlPoints&& cp )
{
    m_cp = std::move(cp);
}

double BezierCurve::Calculate( double percentage )
{
    auto point_count = GetPointCount();

    if( !CheckValidation() )
    {
        LOG_WARNING("WARNING: every bezier curve should at least have 2 or more points for it to be calculated.");
        if( point_count == 1 )
            return m_cp[0];

        else
            return 0; // what else can i do? except exceptions to loose performance.
    }

    if( point_count == 2 )
        return CalculateLinear(m_cp[0],m_cp[1],percentage);

    if( point_count == 3 )
        return CalculateQuadric(m_cp[0],m_cp[1],m_cp[2],percentage);

    if( point_count == 4 )
        return CalculateCubic(m_cp[0],m_cp[1],m_cp[2],m_cp[3], percentage);
}   

void BezierCurve::AddPoint( double point )
{
    if( m_cp.size() <= 3 )
        m_cp.push_back(point);

    else
        LOG_WARNING("WARNING: up to 4 points can exist within a bezier curve");
}

double BezierCurve::CalculateLinear( double p1,double p2, double percentage )
{
    return (1 - percentage) * p1 + percentage * p2;
}

double BezierCurve::CalculateQuadric( double p1,double p2, double p3, double percentage )
{
    return std::pow((1 - percentage),2) * p1 + 2 * ( 1 - percentage ) * p2 + percentage * p3;
}

double BezierCurve::CalculateCubic( double p1,double p2, double p3, double p4, double percentage )
{
    return std::pow((1 - percentage),3) * p1 + 3 * std::pow((1 - percentage),2) * p2 + (1 - percentage) * p3 +
    percentage * p4;
}

void BezierCurve::RemovePointByIndex( uint32_t index )
{
    m_cp.erase(std::next(m_cp.begin(),index));
}

uint32_t BezierCurve::GetPointCount() const
{
    return m_cp.size();
}

bool BezierCurve::CheckValidation() const
{
    auto point_count = GetPointCount();
    return point_count >= 2 && point_count <= 4; // for now we only want to operate on 4 points.
}