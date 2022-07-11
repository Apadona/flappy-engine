#include "texture_manager.hpp"
#include "gl_driver_info.hpp"

TextureManager TextureManager::manager;

TextureManager::TextureSlot::TextureSlot()
{
    Set(0,0);
}

void TextureManager::TextureSlot::Set( GLuint texture_id, GLuint texture_unit )
{
    m_texture_id = texture_id;
    m_texture_unit = texture_unit;
}

void TextureManager::TextureSlot::Clear()
{
    m_texture_id = 0;
    m_texture_unit = 0;
}

bool TextureManager::TextureSlot::IsBound() const
{
    return m_texture_id != 0;
}

bool TextureManager::TextureSlot::IsBoundToTexture( GLuint texture_id ) const
{
    return m_texture_id == texture_id;
}

std::ostream& operator<<( std::ostream& out, const TextureManager& texture_manager )
{
    for( std::size_t i = 0; i < texture_manager.m_texture_slots.capacity(); ++i )
    {
        std::cout << "texture_unit " << i;

        if( texture_manager.m_texture_slots[i].IsBound() )
            std::cout << " is bound.\n";

        else
            std::cout << " is not bound.\n";
    }

    return out;
}

bool TextureManager::Init()
{
    GLHardwareInfo info;
    manager.m_max_texture_slots = info.gl_texture_info.max_texture_units;
    manager.m_texture_slots.reserve(manager.m_max_texture_slots);

    for( int i = 0; i < manager.m_max_texture_slots; ++i )
        manager.m_texture_slots.emplace_back();

    std::cout << manager.m_texture_slots.capacity() << std::endl;

    CORE_LOG_NORMAL("number of texture slots in this hardware:",
                    info.gl_texture_info.max_texture_units);
    return true;
}

bool TextureManager::UseTexture( Texture& texture )
{
    if( auto found = FindTexture(texture); found )
    {
        BindTexture(texture,found.value());
        return true;
    }

    else
    {
        CORE_LOG_HINT("texture with id = ",texture.m_id, " was not registered!");
        auto place = RegisterTexture(texture);

        if( place )
        {
            BindTexture(texture,place.value());
            return true;
        }
    }

    return false;
}

void TextureManager::UnUseTexture( Texture& texture )
{
    if( auto found = FindTexture(texture); found )
        RemoveTexture(texture);
}

std::optional<TextureUnitSize> TextureManager::GetTextureUnitLocation( const Texture& texture )
{
    return FindTexture(texture);
}

bool TextureManager::HasTexture( const Texture& texture ) const
{
    for( auto places : m_texture_slots )
        if( places.IsBoundToTexture(texture.m_id) )
            return true;

    return false;
}

std::optional<TextureUnitSize> TextureManager::RegisterTexture( Texture& texture )
{
    if( texture )
    {
        auto place = FindFirstEmptyTextureSlot();
        if( place )
        {
            m_texture_slots[place.value()].Set(texture.m_id,0);
            return place;
        }

        else
        {
            CORE_LOG_ERROR("cannot bind another texture!\n all texture units are in use.\n");
            return {};
        }
    }

    return {};
}

bool TextureManager::RemoveTexture( const Texture& texture )
{
    for( auto place : m_texture_slots )
        if( place.IsBoundToTexture(texture) )
        {
            place.Clear();
            return true;
        }

    return false;
}

void TextureManager::RemoveAllTextures()
{
    for( auto& i : m_texture_slots )
        i.Clear();
}

std::optional<TextureUnitSize> TextureManager::FindFirstEmptyTextureSlot() const
{
    for( uint16_t i = 0; i < m_texture_slots.size(); ++i )
        if( !( m_texture_slots[i].IsBound() ) )  
            return i;

    return {};
}

std::optional<TextureUnitSize> TextureManager::FindTexture( const Texture& texture ) const
{
    for( uint16_t texture_place = 0; texture_place < m_texture_slots.size(); ++texture_place )
        if( m_texture_slots[texture_place].IsBoundToTexture(texture.m_id) )
            return texture_place;

    return {};
}

void TextureManager::BindTexture( Texture& texture, TextureUnitSize texture_unit, bool bind ) const
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    texture.Bind(bind);
}
