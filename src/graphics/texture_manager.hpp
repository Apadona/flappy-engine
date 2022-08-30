#pragma once

#include "texture.hpp"

using TextureUnitSize = std::uint16_t;

class TextureManager
{
    friend std::ostream& operator<<( std::ostream& out, const TextureManager& texture_manager );

    public:
        TextureManager() = default;

        static bool Init();

        static TextureManager& Get() { return manager; }

        bool UseTexture( Texture& texture );
        void UnUseTexture( Texture& texture );

        std::optional<TextureUnitSize> GetTextureUnitLocation( const Texture& texture ) const;

        void ClearAllTextureSlots();

        bool HasTexture( const Texture& texture ) const;

    private:
        struct TextureSlot
        {
            TextureSlot();
            
            void Set( GLuint texture_id, GLuint m_texture_unit );
            void Clear();

            bool IsBound() const;
            bool IsBoundToTexture( GLuint texture_id ) const;

            GLuint m_texture_id;
            GLuint m_texture_unit;
        };

        std::optional<TextureUnitSize> RegisterTexture( Texture& texture );
        bool RemoveTexture( const Texture& texture );

        void ActivateTextureUnitForTexture( Texture& texture, TextureUnitSize texture_unit,
                              bool activate = true ) const;

        std::optional<TextureUnitSize> FindFirstEmptyTextureSlot() const;
        std::optional<TextureUnitSize> FindTexture( const Texture& texture ) const;

        static TextureManager manager;

        TextureUnitSize m_max_texture_slots;
        std::vector<TextureSlot> m_texture_slots;
};