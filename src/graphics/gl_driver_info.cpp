#include "gl_driver_info.hpp"

#include <glad/glad.h>

GLHardwareInfo::GLHardwareInfo()
{
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &gl_texture_info.max_texture_units);
    //gl_texture_info.max_texture_units = 16;
}