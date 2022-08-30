#include "texture_atlas.hpp"

TextureAtlas::TextureAtlas( Texture& texture, uint16_t size_x, uint16_t size_y, uint32_t total,
                            uint16_t advance_x, uint16_t advance_y )
{
    uint16_t count_x = texture.GetSizeX() / ( size_x + advance_x );
    uint16_t count_y = texture.GetSizeY() / ( size_y + advance_y );

    SetTexture(texture,count_x,count_y,size_x,size_y,total,advance_x,advance_y);
}

TextureAtlas::TextureAtlas( Texture& texture, uint16_t count_x, uint16_t count_y, uint16_t size_x,
                            uint16_t size_y, uint32_t total, uint16_t advance_x,uint16_t advance_y )
                            : m_current_texture(0)
{
    SetTexture(texture,count_x,count_y,size_x,size_y,advance_x,advance_y,total);
}

void TextureAtlas::SetTexture( Texture& texture, uint16_t count_x, uint16_t count_y,
                               uint16_t size_x, uint16_t size_y, uint32_t total,
                               uint16_t advance_x,uint16_t advance_y )
{
    if( !texture )
    {
        LOG_ERROR("the texture passed to texture atlas is invalid!");
        return;
    }

    if( count_x == 0 )
    {
        LOG_ERROR("number of texture atlas rows cannot be zero!\n");
        return;
    }

    if( count_y == 0 )
    {
        LOG_ERROR("number of texture atlas columns cannot be zero!\n");
        return;
    }

    m_texture = &texture;
    m_count_x = count_x, m_count_y = count_y;

    if( !total )  
        m_total_textures = m_count_x * m_count_y;
    else
        m_total_textures = total;

   for( uint32_t i = 0; i < m_total_textures; ++i )
        m_filters.push_back(1);

    m_size_x = size_x, m_size_y = size_y;
    m_advance_x = advance_x, m_advance_y = advance_y;
    m_current_texture = 0;
}

TextureAtlas& TextureAtlas::SetXY( uint32_t x_index, uint32_t y_index )
{
    return Set( ( y_index - 1 ) * m_count_x + x_index );
}

TextureAtlas& TextureAtlas::Set( uint32_t index )
{
    if( index == 0 )
    {
        LOG_ERROR("texture index cannot be 0!\n");
        return *this;
    }

    if( index > m_total_textures )
        return *this; // nothing need to be done in case of out of bind indexing.this will later help with filtering.

    if( !m_texture )
    {
        LOG_ERROR("cannot set a texture atlas whose texture is null!");
        return *this;
    }

    if( m_filter_flag )
        if( !m_filters[index - 1] )
            return *this;

    uint32_t x_index = ( ( index - 1 ) %  m_count_x ) + 1;
    uint32_t y_index = std::ceil( static_cast<float>(index) / m_count_x );

    LOG_NORMAL("x_index:",x_index," y_index:",y_index);

    if( x_index > m_count_x )
    {
        LOG_ERROR("x index in the texture atlas is greater than the number of texture rows!");
        return *this;
    }

    if( y_index > m_count_y )
    {
        LOG_ERROR("y index in the texture atlas is greater than the number of texture columns!");
        return *this;
    }

    m_current_texture = index;

    // calculating ratio and set it into the target texture.
    float x_ratio = static_cast<float>(m_size_x) / m_texture->m_width;
    float y_ratio = static_cast<float>(m_size_y) / m_texture->m_height;

    m_texture->m_sample_ratio.x = x_ratio;
    m_texture->m_sample_ratio.y = y_ratio;

    // calculating offset and set it into the target texture.
    float x_offset = static_cast<float>( ( x_index - 1 ) * ( m_size_x + m_advance_x ) ) / m_texture->m_width;
    float y_offset = static_cast<float>( m_texture->m_height - y_index * ( m_size_y + m_advance_y ) ) / m_texture->m_height;

    m_texture->m_sample_offset.x = x_offset;
    m_texture->m_sample_offset.y = y_offset;

    LOG_NORMAL("x_ratio:",x_ratio," y_ratio:",y_ratio," x_offset:",x_offset," y_offset:",y_offset);

    return *this;
}

TextureAtlas& TextureAtlas::Next()
{
    if( m_current_texture == m_total_textures )
        m_current_texture = 0;

    ++m_current_texture;

    if( m_filter_flag )
        while( !m_filters[m_current_texture] )
            ++m_current_texture;

    return Set(m_current_texture);
}

TextureAtlas::operator bool() const
{
    return m_texture != nullptr;
}

bool TextureAtlas::operator!() const
{
    return m_texture == nullptr;
}