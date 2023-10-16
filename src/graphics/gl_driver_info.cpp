#include "gl_driver_info.hpp"

#include <glad/glad.h>

GLHardwareInfo::GLHardwareInfo()
{
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &gl_texture_info.max_texture_units);

    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT,0,&gl_compute_shader_info.work_group_limit.x);            
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT,1,&gl_compute_shader_info.work_group_limit.y);            
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT,2,&gl_compute_shader_info.work_group_limit.z);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE,0,&gl_compute_shader_info.invocaion_limit.x);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE,1,&gl_compute_shader_info.invocaion_limit.y);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE,2,&gl_compute_shader_info.invocaion_limit.z);
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,&gl_compute_shader_info.max_number_of_invocations);
    glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE,&gl_compute_shader_info.max_shader_block_storage_size);
}