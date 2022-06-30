#include <engine_pch.hpp>

namespace std
{
    // #define M_PI acos(-1.0)

    inline float to_radian( float theta )
    {
        float radian = ( theta / 180.0f ) * M_PI;
        return radian;
    }

    inline float to_theta( float radians )
    {
        float theta = ( radians / M_PI ) * 180.0f;
        return theta;
    }

    inline double to_theta( double radians )
    {
        double theta = ( radians / M_PI ) * 180.0f;
        return theta;
    }

    inline double to_radian( double theta )
    {
        double radian = ( theta / 180.0f ) * M_PI;
        return radian;
    }

    inline long double to_radian( long double theta )
    {
        float radian = ( theta / 180.0f ) * M_PI;
        return radian;
    }

    inline long double to_theta( long double radians )
    {
        long double theta = ( radians / M_PI ) * 180.0f;
        return theta;
    }
}

template<typename T>
Mat2<T> Scale( T scale_x, T scale_y, const Mat2<T>& base )
{
    Mat2<T> temp =
    {
        scale_x,    0,
        0,      scale_y
    };

    return base * temp;
}

template<typename T>
Mat2<T> Rotate( T rotate, const Mat2<T>& base )
{
    Mat2<T> temp =
    {
        std::cos(std::to_radian(rotate)),   -1 * std::sin(std::to_radian(rotate)),
        std::sin(std::to_radian(rotate)),   std::cos(std::to_radian(rotate))
    };

    return base * temp;
}

template<typename T>
Mat3<T> Translate( T move_x, T move_y, const Mat3<T>& base )
{
    Mat3<T> temp =
    {
        1,  0,  move_x,
        0,  1,  move_y,
        0,  0,  1
    };

    return base * temp;
}

template<typename T>
Mat3<T> Scale( T scale_x, T scale_y, T scale_z, const Mat3<T>& base )
{
    Mat3<T> temp =
    {
        scale_x,    0,      0,
        0,      scale_y,    0,
        0,      0,          scale_z
    };

    return base * temp;
}

template<typename T>
Mat3<T> Rotate( T rotate_x, T rotate_y, T rotate_z, const Mat3<T>& base )
{
    Mat3<T> mat_rotate_x, mat_rotate_y, mat_rotate_z;

    auto rotate_x_radian = std::to_radian(rotate_x);
    auto rotate_y_radian = std::to_radian(rotate_y);
    auto rotate_z_radian = std::to_radian(rotate_z);

    if( rotate_x )
    {
        auto cos_x = std::cos(rotate_x_radian);
        auto sin_x = std::sin(rotate_x_radian);

        mat_rotate_x =
        {
            1,          0,          0,
            0,      cos_x,        -sin_x,
            0,      sin_x,         cos_x
        };
    }

    if( rotate_y )
    {
        auto cos_y = std::cos(rotate_y_radian);
        auto sin_y = std::sin(rotate_y_radian);

        mat_rotate_y =
        {
            cos_y,      0,          sin_y,
            0,          1,          0,
           -sin_y,      0,          cos_y
        };
    }

    if( rotate_z )
    {
        auto cos_z = std::cos(rotate_z_radian);
        auto sin_z = std::sin(rotate_z_radian);

        mat_rotate_z =
        {
            cos_z,     -sin_z,      0,
            sin_z,      cos_z,      0,
            0,          0,          1
        };
    }

    return base * (mat_rotate_x * mat_rotate_y * mat_rotate_z);
}

template<typename T>
Mat4<T> Translate( T move_x, T move_y, T move_z, const Mat4<T>& base )
{
    Mat4<T> temp =
    {
        1,  0,  0,  move_x,
        0,  1,  0,  move_y,
        0,  0,  1,  move_z,
        0,  0,  0,  1
    };

    return base * temp;
}

template<typename T>
Mat4<T> Scale( T scale_x, T scale_y, T scale_z, const Mat4<T>& base )
{
    Mat4<T> temp =
    {
        scale_x,    0,      0,      0,
        0,       scale_y,   0,      0,
        0,          0,   scale_z,   0,
        0,          0,      0,      1
    };

    return base * temp;
}

template<typename T>
Mat4<T> Rotate( T rotate_x, T rotate_y, T rotate_z, const Mat4<T>& base )
{
    Mat4<T> mat_rotate_x, mat_rotate_y, mat_rotate_z;

    auto rotate_x_radian = std::to_radian(rotate_x);
    auto rotate_y_radian = std::to_radian(rotate_y);
    auto rotate_z_radian = std::to_radian(rotate_z);

    if( rotate_x )
    {
        auto cos_x = std::cos(rotate_x_radian);
        auto sin_x = std::sin(rotate_x_radian);

        mat_rotate_x =
        {
            1,          0,          0,          0,
            0,      cos_x,        -sin_x,       0,
            0,      sin_x,         cos_x,       0,
            0,          0,          0,          1
        };
    }

    if( rotate_y )
    {
        auto cos_y = std::cos(rotate_y_radian);
        auto sin_y = std::sin(rotate_y_radian);

        mat_rotate_y =
        {
            cos_y,      0,          sin_y,      0,
            0,          1,          0,          0,
           -sin_y,      0,          cos_y,      0,
            0,          0,          0,          1
        };
    }

    if( rotate_z )
    {
        auto cos_z = std::cos(rotate_z_radian);
        auto sin_z = std::sin(rotate_z_radian);

        mat_rotate_z =
        {
            cos_z,     -sin_z,      0,          0,
            sin_z,      cos_z,      0,          0,
            0,          0,          1,          0,
            0,          0,          0,          1
        };
    }

    return base * (mat_rotate_x * mat_rotate_y * mat_rotate_z);
}

template<typename T>
Matrix<4,4,T> LookAt( Vector3D<T> pos, Vector3D<T> target, Vector3D<T> y_up )
{
    auto direction = ( pos - target ).Normal();
    auto right = direction.Cross(y_up).Normal();
    auto up = right.Cross(direction);

    Mat4f mat_1 =
    {   
        right.x,            right.y,            right.z,            1,
        up.x,               up.y,               up.z,               1,
        direction.x,        direction.y,        direction.z,        1,       
        0,                  0,                  0,                  1
    };

    Mat4f mat_2 =
    {
        0,                  0,                  0,          -pos.x,
        0,                  0,                  0,          -pos.y,
        0,                  0,                  0,          -pos.z,
        0,                  0,                  0,              1
    };

    return mat_1 * mat_2;
}

template<typename T>
Matrix<4,4,T> Ortho( T right, T left, T up, T down, T front, T back )
{
    auto x_diff = right - left;
    auto y_diff = up - down;
    auto z_diff = front - back;
    auto x_add = right + left;
    auto y_add = up + down;
    auto z_add = front + back; 

    return
    {
        2 / x_diff,             0,              0,                  0,
        0,                 2 / y_diff,          0,                  0,
        0,                      0,              2 / z_diff,         0,
        x_add / y_diff,    y_add / y_diff,      z_add / z_diff,     1       
    };
}

template<typename T>
Matrix<4,4,T> Perspective( T aspect_ratio, T field_of_view, T plane_near, T plane_far )
{
    auto z_range = plane_near - plane_far;
    auto tan_theta = std::tan(field_of_view / 2);

    return
    {
        1 / aspect_ratio,   0,              0,                          0,
        0,                  1 / tan_theta,  0,                          0,
        0,                  0,              -1,                         1,
        0,                  0,      (2 * plane_far * plane_near) / z_range,         0
    };
}