#version 330 core

layout(location = 0) in vec3 input_pos;
layout(location = 1) in vec2 input_uv;

uniform mat4 transform_matrix;

out vec2 texture_uv;

void main()
{
    texture_uv = input_uv;

    vec4 transformed_vertex = vec4(input_pos,1.0f) * transform_matrix;

    gl_Position = transformed_vertex;
}
