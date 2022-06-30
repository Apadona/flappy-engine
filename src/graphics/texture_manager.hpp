#pragma once

#include "texture.hpp"

class TextureManager
{
    public:
        TextureManager() = default;

        static bool Init();

        static TextureManager& Get() { return manager; }

        void UseTexture( const Texture& texture );
        void UnUseTexture( const Texture& texture );

        void PrintStatus() const;

    private:
        struct TextureSlot
        {
            GLuint texture_unit;
            Texture* texture;
        };

        static TextureManager manager;

        std::vector<Texture*> texture_slots;
};