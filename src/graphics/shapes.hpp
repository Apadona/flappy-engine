#pragma once

#include <vector>

struct Shape
{
    std::vector<float> vertex_pos;
    std::vector<unsigned int> indecies;
    std::vector<float> colors;
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
        }
    };
}