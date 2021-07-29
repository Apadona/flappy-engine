template<typename T>
std::ostream& operator<<( std::ostream& out, const Vector2D<T>& _this )
{
    out << "x:" << _this.x << " y:" << _this.y << std::endl;
    return out;
}

template<typename T>
Vector2D<T>::Vector2D( T first, T second ) : x(first), y(second) {}

template<typename T>
Vector2D<T>::Vector2D( const Vector2D<T>& other ) : x(other.x), y(other.y) {}

template<typename T>
T Vector2D<T>::Dot( const Vector2D<T>& other ) const
{
    return x * other.x + y * other.y;
}

template<typename T>
T Vector2D<T>::Length() const
{
    return sqrt( x * x + y * y );
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator=( const Vector2D<T>& other )
{
    if( this == &other )
        return *this;

    x = other.x;
    y = other.y;

    return *this;
}

template<typename T>
bool Vector2D<T>::operator==( const Vector2D<T>& other ) const
{
    if( this == &other )
        return true;

    return x == other.x && y == other.y;
}

template<typename T>
Vector2D<T> Vector2D<T>::operator+( const T& numeric ) const
{
    return { x + numeric, y + numeric };
}

template<typename T>
Vector2D<T> Vector2D<T>::operator-( const T& numeric ) const
{
    return { x - numeric, y - numeric };
}

template<typename T>
Vector2D<T> Vector2D<T>::operator*( const T& numeric ) const
{
    return { x * numeric, y * numeric };
}

template<typename T>
Vector2D<T> Vector2D<T>::operator/( const T& numeric ) const
{
    if( numeric != 0 )
        return { x / numeric, y / numeric };

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator+=( const T& numeric )
{
    x += numeric, y += numeric;
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator-=( const T& numeric )
{
    x -= numeric, y -= numeric;
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator*=( const T& numeric )
{
    x *= numeric, y *= numeric;
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator/=( const T& numeric )
{
    if( numeric != 0 )
    {
        x /= numeric, y /= numeric;
        return *this;
    }

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector2D<T> Vector2D<T>::operator+( const Vector2D<T>& other ) const
{
    return { x + other.x, y + other.y };
}

template<typename T>
Vector2D<T> Vector2D<T>::operator-( const Vector2D<T>& other ) const
{
    return { x - other.x, y - other.y };
}

template<typename T>
Vector2D<T> Vector2D<T>::operator*( const Vector2D<T>& other ) const
{
    return { x * other.x, y * other.y };
}

template<typename T>
Vector2D<T> Vector2D<T>::operator/( const Vector2D<T>& other ) const
{
    if( other.x != 0 && other.y != 0 )
        return { x / other.x, y / other.y };

    throw MathException(DIVIDE_BY_ZERO);
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator+=( const Vector2D<T>& other )
{
    x += other.x, y += other.y;

    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator-=( const Vector2D<T>& other )
{
    x -= other.x, y -= other.y;
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator*=( const Vector2D<T>& other )
{
    x *= other.x, y *= other.y;
    return *this;
}

template<typename T>
Vector2D<T>& Vector2D<T>::operator/=( const Vector2D<T>& other )
{
    if( other.x != 0 && other.y != 0 )
    {
        x /= other.x, y /= other.y;
        return *this;
    } 

    throw MathException(DIVIDE_BY_ZERO);
}