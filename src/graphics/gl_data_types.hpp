#pragma once

enum GLDataType
{
    // single components.
    BOOL            = 1,
    INT             = 4,
    UINT            = 4,
    FLOAT           = 4,
    DOUBLE          = 8,

    // boolean vector.
    BVEC2           = 2,
    BVEC3           = 3,
    BVEC4           = 4,

    // integer vector.
    IVEC2           = 8,
    IVEC3           = 12,
    IVEC4           = 16,

    // unsigned integer vector.
    UVEC2           = 8,
    UVEC3           = 12,
    UVEC4           = 16,

    // float vector.
    VEC2            = 8,
    VEC3            = 12,
    VEC4            = 16,

    // double vector.
    DVEC2           = 16,
    DVEC3           = 24,
    DVEC4           = 32,

    // matrix(nm) ( n colomns * m rows ). they are all floats.
    MAT22           = 16,
    MAT23           = 24,
    MAT24           = 32,
    MAT32           = 24,
    MAT33           = 36,
    MAT34           = 48,
    MAT42           = 32,
    MAT43           = 48,
    MAT44           = 64
};

inline constexpr int CalculateSize( GLDataType type )
{
    return static_cast<int>(type);
}

inline constexpr int CalculateComponent( GLDataType type )
{
    switch (type)
    {
        case BOOL:
        case INT:
        case UINT:
        case FLOAT:
        case DOUBLE:
            return 1;
        break;

        case BVEC2:
        case IVEC2:
        case UVEC2:
        case VEC2:
        case DVEC2:
            return 2;
        break;

        case BVEC3:
        case IVEC3:
        case UVEC3:
        case VEC3:
        case DVEC3:
            return 3;
        break;

        case BVEC4:
        case IVEC4:
        case UVEC4:
        case VEC4:
        case DVEC4:
            return 4;
        break;

        case MAT22:
            return 4;
        break;

        case MAT23:
        case MAT32:
            return 6;
        break;

        case MAT24:
        case MAT42:
            return 8;
        break;

        case MAT33:
            return 9;
        break;

        case MAT34:
        case MAT43:
            return 12;
        break;

        case MAT44:
            return 16;
        break;    
    }
}

inline constexpr CalculateType( GLDataType type )
{
    switch( type )
    {
        case BOOL:
        case BVEC2:
        case BVEC3:
        case BVEC4:
            return GL_BOOL;
        break;

        case INT:
        case IVEC2:
        case IVEC3:
        case IVEC4:
            return GL_INT;
        break;

        case UINT:
        case UVEC2:
        case UVEC3:
        case UVEC4:
            return GL_UINT;
        break;

        case FLOAT:
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
        break;

        case DOUBLE:
        case DVEC2:
        case DVEC3:
        case DVEC4:
            return GL_DOUBLE;
        break;
    }
}
