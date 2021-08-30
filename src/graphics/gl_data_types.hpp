#pragma once

#include <glad/glad.h>

enum GLDataType
{
    NONE,

    // single components.
    _BOOL,
    INTEGER,
    UINTEGER,
    FLOATING,
    DOUBLE,

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

    // double vector.
    DVEC2,
    DVEC3,
    DVEC4,

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
        
    }
}

inline constexpr GLint CalculateSize( GLDataType type )
{
    switch( type )
    {
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

        case DOUBLE:
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
        case DVEC2:
        case MAT22:
            return 16;

        case DVEC3:
        case MAT23:
        case MAT32:
            return 24;

        case DVEC4:
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
    }
}

inline constexpr GLint CalculateComponent( GLDataType type )
{
    switch ( type )
    {
        case _BOOL:
        case INTEGER:
        case UINTEGER:
        case FLOATING:
        case DOUBLE:
            return 1;

        case BVEC2:
        case IVEC2:
        case UVEC2:
        case VEC2:
        case DVEC2:
            return 2;

        case BVEC3:
        case IVEC3:
        case UVEC3:
        case VEC3:
        case DVEC3:
            return 3;

        case BVEC4:
        case IVEC4:
        case UVEC4:
        case VEC4:
        case DVEC4:
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
    }
}

inline constexpr GLint CalculateType( GLDataType type )
{
    switch( type )
    {
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

        case DOUBLE:
        case DVEC2:
        case DVEC3:
        case DVEC4:
            return GL_DOUBLE;
    }
}
