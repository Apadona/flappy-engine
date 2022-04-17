#pragma once

#include "matrix.hpp"
#include "vector3D.hpp"

template<typename T>
Mat2<T> Scale( T scale_x, T scale_y, const Mat2<T>& base = Mat2<T>() );
template<typename T>
Mat2<T> Rotate( T rotate, const Mat2<T>& base = Mat2<T>() );

template<typename T>
Mat3<T> Translate( T move_x, T move_y, const Mat3<T>& base );
template<typename T>
Mat3<T> Scale( T scale_x, T scale_y, T scale_z, const Mat3<T>& base = Mat3<T>() );
template<typename T>
Mat3<T> Rotate( T rotate_x, T rotate_y, T rotate_z , const Mat3<T>& base = Mat3<T>() );

template<typename T>
Mat4<T> Translate( T move_x, T move_y, T move_z, const Mat4<T>& base = Mat4<T>() );
template<typename T>
Mat4<T> Scale( T scale_x, T scale_y, T scale_z, const Mat4<T>& base = Mat4<T>() );
template<typename T>
Mat4<T> Rotate( T rotate_x, T rotate_y, T rotate_z, const Mat4<T>& base = Mat4<T>() );

template<typename T>
Matrix<4,4,T> LookAt( Vector3D<T> pos, Vector3D<T> target, Vector3D<T> y_up );
template<typename T>
Matrix<4,4,T> Ortho( T right, T left, T up, T down, T front, T back );
template<typename T>
Matrix<4,4,T> Perspective( T aspect_ratio, T field_of_view, T plane_near, T plane_far );

#include "matrix_operations.inl"