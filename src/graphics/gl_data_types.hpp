#pragma once

#include <glad/glad.h>
#include <engine_pch.hpp>

#ifdef DOUBLE
    #undef DOUBLE
#endif

enum struct GLDataType
{
    NONE,

    // single components.
    _BOOL,
    INTEGER,
    UINTEGER,
    FLOATING,
    _DOUBLE,

    // BOOLEAN vector.
    BVEC2,
    BVEC3,
    BVEC4,

    // integer vector.
    IVEC2,
    IVEC3,
    IVEC4,

    // unsigned integer vector.
    UVEC2,
    UVEC3,
    UVEC4,

    // float vector.
    VEC2,
    VEC3,
    VEC4,

    // matrix(nm) ( n colomns * m rows ). they are all floats.
    MAT22,
    MAT23,
    MAT24,
    MAT32,
    MAT33,
    MAT34,
    MAT42,
    MAT43,
    MAT44,

    // Sampler
    TEXTURE_1D,
    TEXTURE_2D,
    TEXTURE_3D,

    TEXTURE_CUBE_MAP
};

inline constexpr GLDataType ConvertType( GLenum data_type )
{
    switch( data_type )
    {
        case GL_BOOL:
            return GLDataType::_BOOL;

        case GL_INT:
            return GLDataType::INTEGER;

        case GL_UNSIGNED_INT:
            return GLDataType::UINTEGER;

        case GL_FLOAT:
            return GLDataType::FLOATING;

        case GL_DOUBLE:
            return GLDataType::_DOUBLE;

        case GL_BOOL_VEC2:
            return GLDataType::BVEC2;

        case GL_BOOL_VEC3:
            return GLDataType::BVEC3;

        case GL_BOOL_VEC4:
            return GLDataType::BVEC4;

        case GL_INT_VEC2:
            return GLDataType::IVEC2;

        case GL_INT_VEC3:
            return GLDataType::IVEC3;

        case GL_INT_VEC4:
            return GLDataType::IVEC4;

        case GL_UNSIGNED_INT_VEC2:
            return GLDataType::UVEC2;

        case GL_UNSIGNED_INT_VEC3:
            return GLDataType::UVEC3;

        case GL_UNSIGNED_INT_VEC4:
            return GLDataType::UVEC4;

        case GL_FLOAT_VEC2:
            return GLDataType::VEC2;

        case GL_FLOAT_VEC3:
            return GLDataType::VEC3;

        case GL_FLOAT_VEC4:
            return GLDataType::VEC4;

        case GL_FLOAT_MAT2:
            return GLDataType::MAT22;
        
        case GL_FLOAT_MAT2x3:
            return GLDataType::MAT23;

        case GL_FLOAT_MAT2x4:
            return GLDataType::MAT24;

        case GL_FLOAT_MAT3x2:
            return GLDataType::MAT32;

        case GL_FLOAT_MAT3:
            return GLDataType::MAT33;

        case GL_FLOAT_MAT3x4:
            return GLDataType::MAT34;

        case GL_FLOAT_MAT4x2:
            return GLDataType::MAT42;

        case GL_FLOAT_MAT4x3:
            return GLDataType::MAT43;

        case GL_FLOAT_MAT4:
            return GLDataType::MAT44;

        case GL_SAMPLER_1D:
            return GLDataType::TEXTURE_1D;

        case GL_SAMPLER_2D:
            return GLDataType::TEXTURE_2D;

        case GL_SAMPLER_3D:
            return GLDataType::TEXTURE_3D;

        case GL_SAMPLER_CUBE:
            return GLDataType::TEXTURE_CUBE_MAP;

        default:
            CORE_LOG_WARNING("certain type of OpenGL data type is not handeled now!\n");
            return GLDataType::NONE;
    }
}

inline constexpr GLint CalculateSize( GLDataType type ) // in BYTES
{
    switch( type )
    {
        case GLDataType::NONE:
            CORE_LOG_WARNING("GLDataType None has no Size!\n");
            return 0;

        case GLDataType::_BOOL:
            return 1;   

        case GLDataType::BVEC2:
            return 2;

        case GLDataType::BVEC3:
            return 3;

        case GLDataType::INTEGER:
        case GLDataType::UINTEGER:
        case GLDataType::FLOATING:
        case GLDataType::BVEC4:
            return 4;

        case GLDataType::_DOUBLE:
        case GLDataType::IVEC2:
        case GLDataType::UVEC2:
        case GLDataType::VEC2:
            return 8;

        case GLDataType::IVEC3:
        case GLDataType::UVEC3:
        case GLDataType::VEC3:
            return 12;

        case GLDataType::IVEC4:
        case GLDataType::UVEC4:
        case GLDataType::VEC4:
        case GLDataType::MAT22:
            return 16;

        case GLDataType::MAT23:
        case GLDataType::MAT32:
            return 24;

        case GLDataType::MAT24:
        case GLDataType::MAT42:
            return 32;

        case GLDataType::MAT33:
            return 36;

        case GLDataType::MAT34:
        case GLDataType::MAT43:
            return 48;

        case GLDataType::MAT44:
            return 64;

        case GLDataType::TEXTURE_1D:
            return 0;

        case GLDataType::TEXTURE_2D:
            return 0;

        case GLDataType::TEXTURE_3D:
            return 0;

        case GLDataType::TEXTURE_CUBE_MAP:
            return 0;


        default:
            CORE_LOG_WARNING("invalid type sent to CalculateSize function!\n");
            return 0;
    }
}

inline constexpr GLint CalculateComponent( GLDataType type )
{
    switch ( type )
    {
        case GLDataType::NONE:
            CORE_LOG_WARNING("GLDataType None has no component!\n");
            return 0;

        case GLDataType::_BOOL:
        case GLDataType::INTEGER:
        case GLDataType::UINTEGER:
        case GLDataType::FLOATING:
        case GLDataType::_DOUBLE:
            return 1;

        case GLDataType::BVEC2:
        case GLDataType::IVEC2:
        case GLDataType::UVEC2:
        case GLDataType::VEC2:
            return 2;

        case GLDataType::BVEC3:
        case GLDataType::IVEC3:
        case GLDataType::UVEC3:
        case GLDataType::VEC3:
            return 3;

        case GLDataType::BVEC4:
        case GLDataType::IVEC4:
        case GLDataType::UVEC4:
        case GLDataType::VEC4:
            return 4;

        case GLDataType::MAT22:
            return 4;

        case GLDataType::MAT23:
        case GLDataType::MAT32:
            return 6;

        case GLDataType::MAT24:
        case GLDataType::MAT42:
            return 8;

        case GLDataType::MAT33:
            return 9;

        case GLDataType::MAT34:
        case GLDataType::MAT43:
            return 12;

        case GLDataType::MAT44:
            return 16;

        case GLDataType::TEXTURE_1D:
            return 0;

        case GLDataType::TEXTURE_2D:
            return 0;

        case GLDataType::TEXTURE_3D:
            return 0;

        case GLDataType::TEXTURE_CUBE_MAP:
            return 0;

        default:
            CORE_LOG_WARNING("invalid type sent to CalculateComponent function!\n");
            return 0;
    }
}

inline constexpr GLint CalculateType( GLDataType type )
{
    switch( type )
    {
        case GLDataType::NONE:
            CORE_LOG_WARNING("GLDataType None has no type!\n");
            return -1;

        case GLDataType::_BOOL:
        case GLDataType::BVEC2:
        case GLDataType::BVEC3:
        case GLDataType::BVEC4:
            return GL_BOOL;

        case GLDataType::INTEGER:
        case GLDataType::IVEC2:
        case GLDataType::IVEC3:
        case GLDataType::IVEC4:
            return GL_INT;
        case GLDataType::UINTEGER:
        case GLDataType::UVEC2:
        case GLDataType::UVEC3:
        case GLDataType::UVEC4:
            return GL_UNSIGNED_INT;

        case GLDataType::FLOATING:
        case GLDataType::VEC2:
        case GLDataType::VEC3:
        case GLDataType::VEC4:
        
        case GLDataType::MAT22:
        case GLDataType::MAT23:
        case GLDataType::MAT24:
        case GLDataType::MAT32:
        case GLDataType::MAT33:
        case GLDataType::MAT34:
        case GLDataType::MAT42:
        case GLDataType::MAT43:
        case GLDataType::MAT44:
            return GL_FLOAT;

        case GLDataType::_DOUBLE:
            return GL_DOUBLE;

        case GLDataType::TEXTURE_1D:
        case GLDataType::TEXTURE_2D:
        case GLDataType::TEXTURE_3D:
        case GLDataType::TEXTURE_CUBE_MAP:
            return GL_TEXTURE;

        default:
            CORE_LOG_WARNING("invalid type sent to CalculateType function!\n");
            return 0;
    }
}
