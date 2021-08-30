#version 330 core

out vec4 final_color;
uniform vec4 input_color;

void main()
{
    final_color = input_color;
}