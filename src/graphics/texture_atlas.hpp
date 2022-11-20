#pragma once

#include "texture.hpp"

class TextureAtlas
{
    public:
        TextureAtlas() = default;

        TextureAtlas( Texture& texture, uint16_t size_x, uint16_t size_y, uint32_t total = 0,
                      uint16_t advance_x = 0, uint16_t advance_y = 0 );

        TextureAtlas( Texture& texture, uint16_t count_x, uint16_t count_y, uint16_t size_x,
                      uint16_t size_y, uint32_t total = 0, uint16_t advance_x = 0,
                      uint16_t advance_y = 0 );

        void SetTexture( Texture& texture, uint16_t count_x, uint16_t count_y, uint16_t size_x,
                         uint16_t size_y, uint32_t total = 0, uint16_t advance_x = 0, 
                         uint16_t advance_y = 0 );

        TextureAtlas& SetCounts( uint16_t count_x, uint16_t count_y )
        {
            m_count_x = count_x;
            m_count_y = count_y;

            return *this;
        }

        TextureAtlas& SetTextureSizes( uint16_t size_x, uint16_t size_y )
        {
            m_size_x = size_x;
            m_size_y = size_y;

            return *this;
        }

        TextureAtlas& SetOffsets( uint16_t advance_x, uint16_t advance_y )
        {
            m_advance_x = advance_x;
            m_advance_y = advance_y;

            return *this;
        }

        void SetFiltering( bool filter_flag ) { m_filter_flag = filter_flag; }

        TextureAtlas& SetFilter( std::uint32_t index, bool ignore_flag )
        {
            m_filters.at(index) = static_cast<uint8_t>(ignore_flag);
            return *this;
        }

        TextureAtlas& SetFilter( std::vector<uint8_t>& filters )
        {
            m_filters = filters;
            return *this;
        }

        TextureAtlas& Set( uint32_t index );
        TextureAtlas& SetXY( uint32_t x_index, uint32_t y_index );
        // advances to the next texture piece.
        TextureAtlas& Next();

        Texture* GetTexture() { return m_texture; }
        Vec2ui GetOffsets() const { return {m_count_x,m_count_y}; }
        const std::vector<uint8_t> GetFilters() const { return m_filters; }

        operator bool() const;
        bool operator!() const;

    protected:
        uint32_t m_current_texture;

        Texture* m_texture;

        uint16_t m_count_x;
        uint16_t m_count_y;
        uint32_t m_total_textures;

        uint16_t m_size_x;
        uint16_t m_size_y;

        uint16_t m_advance_x;
        uint16_t m_advance_y;

        std::vector<uint8_t> m_filters;
        bool m_filter_flag = false;
};