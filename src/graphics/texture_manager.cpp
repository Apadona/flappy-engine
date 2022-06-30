#include "texture_manager.hpp"
#include "gl_driver_info.hpp"

TextureManager TextureManager::manager;

bool TextureManager::Init()
{
    GLHardwareInfo info;
    manager.texture_slots.reserve(info.gl_texture_info.max_texture_units);
    
    for( auto& ref : manager.texture_slots )
        ref = nullptr;

    LOG_NORMAL("number of texture slots in this hardware:",info.gl_texture_info.max_texture_units);
    return true;
}

void TextureManager::UseTexture( const Texture& texture )
{
    GLuint found_texture_place  = 0;
    bool found_first_empty_place = false;

    for( std::size_t i = 0; i < texture_slots.capacity(); ++i )
    {
        // if we find an empty place, we will store that place(only the first found emptied place should be assigned).
        if( texture_slots[i] == nullptr && !found_first_empty_place )  
        {
            found_texture_place = i;
            found_first_empty_place = true;
        }

        // if the texture is already assigned to a unit, we can use that.
        if( texture_slots[i] == &texture )
        {
            found_texture_place = i;
            break;
        }
    }

    texture_slots[found_texture_place] = const_cast<Texture*>(&texture);

    glActiveTexture(GL_TEXTURE0 + found_texture_place);
}

void TextureManager::UnUseTexture( const Texture& texture )
{
    for( std::size_t i = 0; i < texture_slots.size(); ++i )
    {
        if( texture_slots[i] == &texture )
        {
            texture_slots[i] = nullptr;
            break;
        }
    }
}

void TextureManager::PrintStatus() const
{
    for( std::size_t i = 0; i < texture_slots.capacity(); ++i )
    {
        std::cout << "texture_unit " << i;

        if( texture_slots[i] != nullptr )
            std::cout << " is bound.\n";

        else
            std::cout << " is not bound.\n";
    }

    //std::cout << std::endl;
}
