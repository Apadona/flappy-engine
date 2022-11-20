#version 330 core

in vec2 texture_uv;

uniform sampler2D texture_image01;
uniform vec2 sample_offset;
uniform vec2 sample_ratio;

uniform vec4 blend_color;

out vec4 final_color;

void main()
{
    final_color = texture(texture_image01,texture_uv * sample_ratio + sample_offset) * blend_color;
}