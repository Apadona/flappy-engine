#version 330 core

uniform sampler2D texture_image01;

uniform vec4 blend_color;

in vec2 texture_uv;
out vec4 final_color;

void main()
{
    final_color = texture(texture_image01,texture_uv) * blend_color;
}