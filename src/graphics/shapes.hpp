#pragma once

#include <engine_pch.hpp>

struct Shape
{/*
    Shape() = default;
    Shape( const Shape& other );
    Shape( Shape&& other );
    Shape( std::vector<float>& vertex_pos, std::vector<uint32_t>& indecies, std::vector<float>& color,
         std::vector<float>& texture_uv );


    Shape& operator=( const Shape& other );
    Shape& operator=( Shape&& other );*/

    std::vector<float> vertex_pos;
    std::vector<uint32_t> indecies;
    std::vector<float> color;
    std::vector<float> texture_uv;/*

    inline static constexpr Shape triangle =
    {
        {
            0.0f,   0.86f,  1.0f,
            -0.5f,   0.0f,  1.0f,
            0.5f,   0.0f,  1.0f
        },

        {
            0,1,2
        },

        {
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,0.0f,1.0f
        },

        {
            0.5f,1.0f,
            0.0f,0.0f,
            1.0f,0.0f
        }
    };

    inline static constexpr Shape rectangle =
    {
        {
            0.5f,   0.5f,   1.0f,
            -0.5f,   0.5f,    1.0f,
            -0.5f,   -0.5f,   1.0f,
            0.5f,   -0.5f,   1.0f
        },

        {
            0,1,2,
            2,3,0
        },

        {
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,0.0f,1.0f,
            1.0f,1.0f,0.0f
        },

        {
            1.0f,1.0f,
            0.0f,1.0f,
            0.0f,0.0f,
            1.0f,0.0f
        }
    };*/
};

namespace
{
    Shape triangle =
    {
        {
            0.0f,   0.86f,  1.0f,
            -0.5f,   0.0f,  1.0f,
            0.5f,   0.0f,  1.0f
        },

        {
            0,1,2
        },

        {
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,0.0f,1.0f
        },

        {
            0.5f,1.0f,
            0.0f,0.0f,
            1.0f,0.0f
        }
    };

    Shape rectangle = 
    {
        {
            0.5f,   0.5f,   1.0f,
            -0.5f,   0.5f,    1.0f,
            -0.5f,   -0.5f,   1.0f,
            0.5f,   -0.5f,   1.0f
        },

        {
            0,1,2,
            2,3,0
        },

        {
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,0.0f,1.0f,
            1.0f,1.0f,0.0f
        },

        {
            1.0f,1.0f,
            0.0f,1.0f,
            0.0f,0.0f,
            1.0f,0.0f
        }
    };
}