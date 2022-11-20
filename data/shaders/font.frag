#version 330 core

uniform sampler2D texture_image01;
uniform vec2 sample_offset;
uniform vec2 sample_ratio;

uniform vec4 blend_color;

in vec2 texture_uv;
out vec4 final_color;

void main()
{
    vec4 sampled = vec4(1.0,1.0,1.0,texture(texture_image01,texture_uv * sample_ratio + sample_offset).r);
    final_color = sampled * blend_color;
}