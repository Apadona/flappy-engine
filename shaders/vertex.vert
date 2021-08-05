#version 130 core

in vec2 pos;

void main()
{
    gl_Position = vec4(pos.x,pos.y,0.0f,0.0f);
}
