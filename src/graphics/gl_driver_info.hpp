#pragma once

#include <engine_pch.hpp>
#include <maths/vector3D.hpp>

struct GLDriverTextureInfo
{
    std::int32_t max_texture_units;
};

struct GLDriverComputeShaderInfo
{
    Vec3i work_group_limit;
    Vec3i invocaion_limit;
    int32_t max_number_of_invocations;
    int32_t max_shader_block_storage_size;
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
    GLDriverComputeShaderInfo gl_compute_shader_info;
    /*
    GLDriverBufferInfo gl_buffer_info;
    GLDriverUniformInfo gl_uniform_info;
    GLDriverFrameBufferInfo gl_framebuffer_info;
    */
};