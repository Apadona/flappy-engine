#pragma once

#include <engine_pch.hpp>

struct Shape
{
    std::vector<float> vertex_pos;
    std::vector<unsigned int> indecies;
    std::vector<float> color;
    std::vector<float> texture_uv;
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