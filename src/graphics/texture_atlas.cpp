#include "texture_atlas.hpp"

TextureAtlas::TextureAtlas()
{
    Reset();
}

TextureAtlas::TextureAtlas( Texture& texture )
{
    m_texture = &texture;
    m_count_x = 1, m_count_y = 1;
    m_total_textures = 1;
    m_size_x = texture.GetSizeX(), m_size_y = texture.GetSizeY();
    m_advance_x = 1, m_advance_y = 1;
    m_current_index = 0;
}

TextureAtlas::TextureAtlas( Texture& texture, uint16_t size_x, uint16_t size_y, uint32_t total,
                            uint16_t advance_x, uint16_t advance_y )
{
    uint16_t count_x = texture.GetSizeX() / ( size_x + advance_x );
    uint16_t count_y = texture.GetSizeY() / ( size_y + advance_y );

    SetTexture(texture,count_x,count_y,size_x,size_y,total,advance_x,advance_y);
}

TextureAtlas::TextureAtlas( Texture& texture, uint16_t count_x, uint16_t count_y, uint16_t size_x,
                            uint16_t size_y, uint32_t total, uint16_t advance_x,uint16_t advance_y )
                            : m_current_index(0)
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

    if( size_x == 0 )
        m_size_x = m_texture->GetSizeX();
    else
        m_size_x = size_x;

    if( size_y == 0 )
        m_size_y = m_texture->GetSizeY();

    else
        m_size_y = size_y;

    m_advance_x = advance_x, m_advance_y = advance_y;
    m_current_index = 0;
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
        return *this; // nothing needs to be done in case of out of bound indexing.this will later help with filtering.

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

    m_current_index = index;

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

    // LOG_NORMAL("x_ratio:",x_ratio," y_ratio:",y_ratio," x_offset:",x_offset," y_offset:",y_offset);

    return *this;
}

TextureAtlas& TextureAtlas::Next()
{
    if( m_current_index == m_total_textures )
        m_current_index = 0;

    ++m_current_index;

    if( m_filter_flag )
        while( !m_filters[m_current_index] )
            ++m_current_index;

    return Set(m_current_index);
}

void TextureAtlas::SetChangeTime( double change_time )
{
    m_change_time = change_time <= 0 ? 0 : change_time;
}

void TextureAtlas::ProceedByTime( double dt )
{
    if( m_change_time == 0 )
    {
        CORE_LOG_ERROR("the total change time of texture atlas is zero! set it first before calling ProceedByTime!");
        return;
    }

    m_spent_time += dt;

    if( m_spent_time >= m_change_time )
    {
        while( m_spent_time > m_change_time )
        {
            Next();
            m_spent_time -= m_change_time;
        }
    }
}

void TextureAtlas::Reset()
{
    m_texture = nullptr;
    m_current_index = 0;

    m_count_x = 1;
    m_count_y = 1;
    m_total_textures = 1;

    m_size_x = 0;
    m_size_y = 0;

    m_advance_x = 0;
    m_advance_y = 0;

    m_change_time = 0;
    m_spent_time = 0;

    m_filters.clear();
    m_filter_flag = false;
}

TextureAtlas::operator bool() const
{
    return m_texture != nullptr;
}

bool TextureAtlas::operator!() const
{
    return m_texture == nullptr;
}