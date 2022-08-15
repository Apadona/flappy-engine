#pragma once

#include "transform_2D.hpp"
#include "texture.hpp"
#include <maths/vector4D.hpp>

class Sprite
{
    friend class Renderer;

    public:
        Sprite();
        Sprite( Texture& texture, const Transform2D& transform = {},
                const Vec4f& color = {1.0f,1.0f,1.0f,0.0f} );
        Sprite( const Sprite& other );
        Sprite( Sprite&& other );

        Sprite& operator=( const Sprite& other );
        Sprite& operator=( Sprite&& other );

        void SetTexture( Texture& texture ) { if( texture ) m_texture = &texture; }
        void SetTransform( const Transform2D& transform ) { m_transform = transform; }
        void SetColor( const Vec4f& color ) { m_color = color; }

        Texture* GetTexture() { return m_texture; }
        Transform2D& GetTransform() { return m_transform; }
        Vec4f& GetColor() { return m_color; }

    private:
        Texture* m_texture;
        Transform2D m_transform;
        Vec4f m_color;
};