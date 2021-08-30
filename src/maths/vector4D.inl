template<typename U>
std::ostream& operator<<( std::ostream& out, const Vector4D<U>& _this )
{
    out << "x:" << _this.x << " y:" << _this.y << " z:" << _this.z << " w:" << _this.w << std::endl;
    return out;
}

template<typename T>
Vector4D<T>::Vector4D( T first, T second, T third, T forth ) : x(first), y(second), z(third), w(forth) {}

template<typename T>
Vector4D<T>::Vector4D( const Vector4D<T>& other ) : x(other.x), y(other.y), z(other.z), w(other.w) {}

template<typename T>
T Vector4D<T>::Dot( const Vector4D<T>& other ) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

template<typename T>
T Vector4D<T>::Length() const
{
    return sqrt( x * x + y * y + z * z + w * w );
}

template<typename T>
Vector4D<T> Vector4D<T>::Normal() const
{
    T length = Normal();

    if( length )
        return { x / length, y / length, z / length, w / length };

    LOG_SOURCE(LogLevel::DEBUG);
    throw MathException(VECTOR_ZERO_LENGTH_NORAML_CALCULATE);
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator=( const Vector4D<T>& other )
{
    if( this == &other )
        return *this;

    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    return *this;
}

template<typename T>
bool Vector4D<T>::operator==( const Vector4D<T>& other ) const
{
    if( this == &other )
        return true;

    return x == other.x && y == other.y && z == other.z && w == other.w;
}

template<typename T>
Vector4D<T> Vector4D<T>::operator+( const T& numeric ) const
{
    return { x + numeric, y + numeric, z + numeric, w + numeric };
}

template<typename T>
Vector4D<T> Vector4D<T>::operator-( const T& numeric ) const
{
    return { x - numeric, y - numeric, z - numeric, w - numeric };
}

template<typename T>
Vector4D<T> Vector4D<T>::operator*( const T& numeric ) const
{
    return { x * numeric, y * numeric, z * numeric, w * numeric };
}

template<typename T>
Vector4D<T> Vector4D<T>::operator/( const T& numeric ) const
{
    if( numeric != 0 )
        return { x / numeric, y / numeric, z / numeric, w / numeric };

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator+=( const T& numeric )
{
    x += numeric, y += numeric, z += numeric, w += numeric;
    return *this;
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator-=( const T& numeric )
{
    x -= numeric, y -= numeric, z -= numeric, w -= numeric;
    return *this;
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator*=( const T& numeric )
{
    x *= numeric, y *= numeric, z *= numeric, w *= numeric;
    return *this;
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator/=( const T& numeric )
{
    if( numeric != 0 )
    {
        x /= numeric, y /= numeric, z /= numeric, w /= numeric;
        return *this;
    }

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector4D<T> Vector4D<T>::operator+( const Vector4D<T>& other ) const
{
    return { x + other.x, y + other.y, z + other.z, w + other.w };
}

template<typename T>
Vector4D<T> Vector4D<T>::operator-( const Vector4D<T>& other ) const
{
    return { x - other.x, y - other.y, z - other.z, w - other.w };
}

template<typename T>
Vector4D<T> Vector4D<T>::operator*( const Vector4D<T>& other ) const
{
    return { x * other.x, y * other.y, z * other.z, w * other.w };
}

template<typename T>
Vector4D<T> Vector4D<T>::operator/( const Vector4D<T>& other ) const
{
    if( other.x != 0 && other.y != 0 && other.z != 0 && other.w != 0 )
        return { x / other.x, y / other.y, z / other.z, w / other.w };

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator+=( const Vector4D<T>& other )
{
    x += other.x, y += other.y, z += other.z, w += other.w;

    return *this;
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator-=( const Vector4D<T>& other )
{
    x -= other.x, y -= other.y, z -= other.z, w -= other.w;
    return *this;
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator*=( const Vector4D<T>& other )
{
    x *= other.x, y *= other.y, z *= other.z, w *= other.w;
    return *this;
}

template<typename T>
Vector4D<T>& Vector4D<T>::operator/=( const Vector4D<T>& other )
{
    if( other.x != 0 && other.y != 0 && other.z != 0 && other.w != 0 )
    {
        x /= other.x, y /= other.y, z /= other.z, w /= other.w;
        return *this;
    } 

    throw MathException(DIVIDE_BY_ZERO);
}