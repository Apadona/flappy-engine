#include "sprite.hpp"

Sprite::Sprite() : m_texture(nullptr), m_transform(), m_color(1.0f,1.0f,1.0f,0.0f) {}

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
    *this = std::move(other);
}

Sprite& Sprite::operator=( const Sprite& other )
{
    if( this != &other )
    {
        auto _texture = other.m_texture;
        SetTexture(*_texture);
        SetTransform(other.m_transform);
        SetColor(other.m_color);
    }

    return *this;
}

Sprite& Sprite::operator=( Sprite&& other )
{
    m_texture = other.m_texture;
    m_transform = other.m_transform;
    m_color = other.m_color;

    other.m_texture = nullptr;
    other.m_transform = {};
    other.m_color = {};

    return *this;
}