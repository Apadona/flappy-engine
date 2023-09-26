#pragma once

#include <engine_pch.hpp>

class BezierCurve
{
    public:
        using ControlPoints = std::vector<float>;
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

        float Calculate( float percentage );

        void AddPoint( float point );
        void RemovePointByIndex( uint32_t index );

        void SetControlPoints( const ControlPoints& cp );
        const ControlPoints& GetControlPoints() const;

        uint32_t GetPointCount() const;

        static float CalculateLinear( float p1,float p2, float percentage );
        static float CalculateQuadric( float p1, float p2, float p3, float percentage );
        static float CalculateCubic( float p1,float p2, float p3, float p4, float percentage );

    private:
        bool CheckValidation() const;

    private:
        ControlPoints m_cp;
};