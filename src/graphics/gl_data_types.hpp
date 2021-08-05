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
