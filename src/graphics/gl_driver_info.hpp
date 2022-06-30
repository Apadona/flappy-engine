#pragma once

#include <cstdint>

struct GLDriverTextureInfo
{
    std::int32_t max_texture_units;
};
/*
struct GLDriverBufferInfo
{

};

struct GLDriverUniformInfo
{

};

struct GLDriverFrameBufferInfo
{

};
*/

struct GLHardwareInfo
{
    GLHardwareInfo();

    GLDriverTextureInfo gl_texture_info;
    /*
    GLDriverBufferInfo gl_buffer_info;
    GLDriverUniformInfo gl_uniform_info;
    GLDriverFrameBufferInfo gl_framebuffer_info;
    */
};