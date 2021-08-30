#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 transform_matrix;
uniform vec4 input_color;

void main()
{
    vec4 transformed_vertex = vec4(pos,1.0f) * transform_matrix;
    gl_Position = transformed_vertex;
}
