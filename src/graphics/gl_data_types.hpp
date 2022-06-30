#pragma once

#include <glad/glad.h>
#include <engine_pch.hpp>

#ifdef DOUBLE
    #undef DOUBLE
#endif

enum GLDataType
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
};

inline constexpr GLDataType ConvertType( GLenum data_type )
{
    switch( data_type )
    {
        case GL_BOOL:
            return _BOOL;

        case GL_INT:
            return INTEGER;

        case GL_UNSIGNED_INT:
            return UINTEGER;

        case GL_FLOAT:
            return FLOATING;

        case GL_DOUBLE:
            return _DOUBLE;

        case GL_BOOL_VEC2:
            return BVEC2;

        case GL_BOOL_VEC3:
            return BVEC3;

        case GL_BOOL_VEC4:
            return BVEC4;

        case GL_INT_VEC2:
            return IVEC2;

        case GL_INT_VEC3:
            return IVEC3;

        case GL_INT_VEC4:
            return IVEC4;

        case GL_UNSIGNED_INT_VEC2:
            return UVEC2;

        case GL_UNSIGNED_INT_VEC3:
            return UVEC3;

        case GL_UNSIGNED_INT_VEC4:
            return UVEC4;

        case GL_FLOAT_VEC2:
            return VEC2;

        case GL_FLOAT_VEC3:
            return VEC3;

        case GL_FLOAT_VEC4:
            return VEC4;

        case GL_FLOAT_MAT2:
            return MAT22;
        
        case GL_FLOAT_MAT2x3:
            return MAT23;

        case GL_FLOAT_MAT2x4:
            return MAT24;

        case GL_FLOAT_MAT3x2:
            return MAT32;

        case GL_FLOAT_MAT3:
            return MAT33;

        case GL_FLOAT_MAT3x4:
            return MAT34;

        case GL_FLOAT_MAT4x2:
            return MAT42;

        case GL_FLOAT_MAT4x3:
            return MAT43;

        case GL_FLOAT_MAT4:
            return MAT44;

        default:
            LOG_WARNING("certain type of OpenGL data type is not handeled now!\n");
            return NONE;
    }
}

inline constexpr GLint CalculateSize( GLDataType type ) // in BYTES
{
    switch( type )
    {
        case NONE:
            LOG_WARNING("GLDataType None has no Size!\n");
            return 0;

        case _BOOL:
            return 1;   

        case BVEC2:
            return 2;

        case BVEC3:
            return 3;

        case INTEGER:
        case UINTEGER:
        case FLOATING:
        case BVEC4:
            return 4;

        case _DOUBLE:
        case IVEC2:
        case UVEC2:
        case VEC2:
            return 8;

        case IVEC3:
        case UVEC3:
        case VEC3:
            return 12;

        case IVEC4:
        case UVEC4:
        case VEC4:
        case MAT22:
            return 16;

        case MAT23:
        case MAT32:
            return 24;

        case MAT24:
        case MAT42:
            return 32;

        case MAT33:
            return 36;

        case MAT34:
        case MAT43:
            return 48;

        case MAT44:
            return 64;

        default:
            LOG_WARNING("invalid type sent to CalculateSize function!\n");
            return 0;
    }
}

inline constexpr GLint CalculateComponent( GLDataType type )
{
    switch ( type )
    {
        case NONE:
            LOG_WARNING("GLDataType None has no component!\n");
            return 0;

        case _BOOL:
        case INTEGER:
        case UINTEGER:
        case FLOATING:
        case _DOUBLE:
            return 1;

        case BVEC2:
        case IVEC2:
        case UVEC2:
        case VEC2:
            return 2;

        case BVEC3:
        case IVEC3:
        case UVEC3:
        case VEC3:
            return 3;

        case BVEC4:
        case IVEC4:
        case UVEC4:
        case VEC4:
            return 4;

        case MAT22:
            return 4;

        case MAT23:
        case MAT32:
            return 6;

        case MAT24:
        case MAT42:
            return 8;

        case MAT33:
            return 9;

        case MAT34:
        case MAT43:
            return 12;

        case MAT44:
            return 16;

        default:
            LOG_WARNING("invalid type sent to CalculateComponent function!\n");
            return 0;
    }
}

inline constexpr GLint CalculateType( GLDataType type )
{
    switch( type )
    {
        case NONE:
            LOG_WARNING("GLDataType None has no type!\n");
            return NONE;

        case _BOOL:
        case BVEC2:
        case BVEC3:
        case BVEC4:
            return GL_BOOL;

        case INTEGER:
        case IVEC2:
        case IVEC3:
        case IVEC4:
            return GL_INT;
        case UINTEGER:
        case UVEC2:
        case UVEC3:
        case UVEC4:
            return GL_UNSIGNED_INT;

        case FLOATING:
        case VEC2:
        case VEC3:
        case VEC4:
        
        case MAT22:
        case MAT23:
        case MAT24:
        case MAT32:
        case MAT33:
        case MAT34:
        case MAT42:
        case MAT43:
        case MAT44:
            return GL_FLOAT;

        case _DOUBLE:
            return GL_DOUBLE;

        default:
            LOG_WARNING("invalid type sent to CalculateType function!\n");
            return 0;
    }
}
