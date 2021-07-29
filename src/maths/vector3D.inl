template<typename T>
std::ostream& operator<<( std::ostream& out, const Vector3D<T>& _this )
{
    out << "x:" << _this.x << " y:" << _this.y << " z:" << _this.z << std::endl;
    return out;
}

template<typename T>
Vector3D<T>::Vector3D( T first, T second, T third ) : x(first), y(second), z(third) {}

template<typename T>
Vector3D<T>::Vector3D( const Vector3D<T>& other ) : x(other.x), y(other.y), z(other.z) {}

template<typename T>
T Vector3D<T>::Dot( const Vector3D<T>& other ) const
{
    return x * other.x + y * other.y + z * other.z;
}

template<typename T>
Vector3D<T> Vector3D<T>::Cross( const Vector3D<T>& other ) const
{
    return { y * other.z - z * other.y,
             x * other.z - z * other.x,
             x * other.y - y * other.x };
}

template<typename T>
T Vector3D<T>::Length() const
{
    return sqrt( x * x + y * y + z * z );
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator=( const Vector3D<T>& other )
{
    if( this == &other )
        return *this;

    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template<typename T>
bool Vector3D<T>::operator==( const Vector3D<T>& other ) const
{
    if( this == &other )
        return true;

    return x == other.x && y == other.y && z == other.z;
}

template<typename T>
Vector3D<T> Vector3D<T>::operator+( const T& numeric ) const
{
    return { x + numeric, y + numeric, z + numeric };
}

template<typename T>
Vector3D<T> Vector3D<T>::operator-( const T& numeric ) const
{
    return { x - numeric, y - numeric, z - numeric };
}

template<typename T>
Vector3D<T> Vector3D<T>::operator*( const T& numeric ) const
{
    return { x * numeric, y * numeric, z * numeric };
}

template<typename T>
Vector3D<T> Vector3D<T>::operator/( const T& numeric ) const
{
    if( numeric != 0 )
        return { x / numeric, y / numeric, z / numeric };

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator+=( const T& numeric )
{
    x += numeric, y += numeric, z += numeric;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator-=( const T& numeric )
{
    x -= numeric, y -= numeric, z -= numeric;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator*=( const T& numeric )
{
    x *= numeric, y *= numeric, z *= numeric;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator/=( const T& numeric )
{
    if( numeric != 0 )
    {
        x /= numeric, y /= numeric, z /= numeric;
        return *this;
    }

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector3D<T> Vector3D<T>::operator+( const Vector3D<T>& other ) const
{
    return { x + other.x, y + other.y, z + other.z };
}

template<typename T>
Vector3D<T> Vector3D<T>::operator-( const Vector3D<T>& other ) const
{
    return { x - other.x, y - other.y, z - other.z };
}

template<typename T>
Vector3D<T> Vector3D<T>::operator*( const Vector3D<T>& other ) const
{
    return { x * other.x, y * other.y, z * other.z };
}

template<typename T>
Vector3D<T> Vector3D<T>::operator/( const Vector3D<T>& other ) const
{
    if( other.x != 0 && other.y != 0 && other.z != 0 )
        return { x / other.x, y / other.y, z / other.z };

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator+=( const Vector3D<T>& other )
{
    x += other.x, y += other.y, z += other.z;

    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator-=( const Vector3D<T>& other )
{
    x -= other.x, y -= other.y, z -= other.z;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator*=( const Vector3D<T>& other )
{
    x *= other.x, y *= other.y, z *= other.z;
    return *this;
}

template<typename T>
Vector3D<T>& Vector3D<T>::operator/=( const Vector3D<T>& other )
{
    if( other.x != 0 && other.y != 0 && other.z != 0 )
    {
        x /= other.x, y /= other.y, z /= other.z;
        return *this;
    } 

    throw MathException(DIVIDE_BY_ZERO);
}