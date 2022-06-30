#include "sprite.hpp"

Sprite::Sprite( const Texture& texture, const Transform2D& transform, const Vec4& color )
{
    SetTexture(texture);
    SetTransform(transform);
    SetColor(color);
}

Sprite::Sprite( const Sprite& other )
{
    *this = other;
}

Sprite::Sprite( Sprite&& other )
{
    *this = std::forward<Sprite>(other);
}

Sprite& Sprite::operator=( const Sprite& other )
{
    if( this != &other )
    {
        SetTexture(other.GetTexture());
        SetTransform(other.m_transform);
        SetColor(other.m_color);
    }
}

Sprite& Sprite::operator=( Sprite&& other )
{
    m_texture = other.m_texture;
    m_transform = other.m_transform;
    m_color = other.m_color;

    other.m_texture = nullptr;
    other.m_transform = {};
    other.m_color = {};
}