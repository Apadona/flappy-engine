#pragma once

#include <engine_pch.hpp>

class BezierCurve
{
    public:
        using ControlPoints = std::vector<double>;
    public:
        BezierCurve() = default;
        BezierCurve( const BezierCurve& bc );
        explicit BezierCurve( BezierCurve&& bc );
        BezierCurve( const ControlPoints& cp );
        explicit BezierCurve( ControlPoints&& cp );

        BezierCurve& operator=( const BezierCurve& other );
        BezierCurve& operator=( const ControlPoints& other );

        BezierCurve& operator=( BezierCurve&& other );
        BezierCurve& operator=( ControlPoints&& points );

        double Calculate( double percentage );

        void AddPoint( double point );
        void RemovePointByIndex( uint32_t index );

        void SetControlPoints( const ControlPoints& cp );
        const ControlPoints& GetControlPoints() const;

        uint32_t GetPointCount() const;

        static double CalculateLinear( double p1,double p2, double percentage );
        static double CalculateQuadric( double p1, double p2, double p3, double percentage );
        static double CalculateCubic( double p1,double p2, double p3, double p4, double percentage );

    private:
        bool CheckValidation() const;

    private:
        ControlPoints m_cp;
};