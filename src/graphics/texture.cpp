#include "texture.hpp"
#include "texture_manager.hpp"

#include <stb_image/stb_image.h>

namespace
{
    inline constexpr GLint GetGLTextureType( TextureType type )
    {
        switch( type )
        {
            case TextureType::INVALID:
                return -1;

            case TextureType::TEXTURE_1D:
                return GL_TEXTURE_1D;

            case TextureType::TEXTURE_2D:
                return GL_TEXTURE_2D;

            case TextureType::TEXTURE_3D:
                return GL_TEXTURE_3D;

            case TextureType::TEXTURE_ARRAY_1D:
                return GL_TEXTURE_1D_ARRAY;

            case TextureType::TEXTURE_ARRAY_2D:
                return GL_TEXTURE_2D_ARRAY;

            case TextureType::TEXTURE_CUBEMAP:
                return GL_TEXTURE_CUBE_MAP;

            case TextureType::TEXTURE_ARRAY_CUBE_MAP:
                return 0x9009; // was not existent in my gl header!

            default:
                CORE_LOG_WARNING("invalid texture type sent to GetGLTextureType function!\n");
                return -1;
        }
    }

    inline constexpr GLint GetGLTextureFormat( TextureFormat format )
    {
        if( format == TextureFormat::RGB )
            return GL_RGB;

        if ( format == TextureFormat::RGBA )
            return GL_RGBA;

        return -1; // invlaid format.
    }

    inline constexpr GLint GetGLTextureFilter( TextureFiltering filter )
    {
        if( filter == TextureFiltering::LINEAR )
            return GL_LINEAR;

        if ( filter == TextureFiltering::NEAREST )
            return GL_NEAREST;

        return -1; // invalid.
    }

    inline constexpr GLint GetGLTextureWrap( TextureWrapping wrapping_method )
    {
        switch( wrapping_method )
        {
            case TextureWrapping::REPEAT:
                return GL_REPEAT;

            case TextureWrapping::MIRRORED_REPEAT:
                return GL_MIRRORED_REPEAT;

            case TextureWrapping::CLAMP_TO_EDGE:
                return GL_CLAMP_TO_EDGE;

            case TextureWrapping::CLAMP_TO_BORDER:
                return GL_CLAMP_TO_BORDER;

            default:
                return -1; // invalid.
        }
    }
}

static Texture* Create( const std::string& texture_file_path )
{
    Texture texture(texture_file_path);

    if( texture )
    {
        if( TextureManager::Get().UseTexture(texture) )
            return &texture;

        else
        {
            CORE_LOG_ERROR("could not register texture");
            return nullptr;
        }
    }

    return nullptr;
}

Texture::Texture( const std::string& texture_file_path )
{
    if( !Create( texture_file_path ) )
        CORE_LOG_ERROR("could not make the texture");
}

Texture::Texture( TextureType type, GLint width, GLint height, unsigned char* data, TextureFormat format )
{
    if( !Create(type,width,height,data,format) )
        CORE_LOG_ERROR("could not make the texture");
}

Texture::Texture( Texture&& other )
{
    if( other.m_type != TextureType::INVALID && this != &other )
        *this = std::move(other); // invoking the move assignment operand.
}

Texture::~Texture()
{
    if( TextureManager::Get().HasTexture(*this) )
        TextureManager::Get().UnUseTexture(*this);

    glBindTexture(GetGLTextureType(m_type),0);
    glDeleteTextures(1,&m_id);
}

Texture& Texture::operator=( Texture&& other )
{
    m_id = other.m_id;
    m_width = other.m_width;
    m_height = other.m_height;
    m_type = other.m_type;
    m_data = other.m_data;
    m_filter_method = other.m_filter_method;
    m_wrap_method = other.m_wrap_method;

    other.m_id = 0;
    other.m_width = 0;
    other.m_height = 0;
    other.m_type = TextureType::INVALID;
    other.m_data = nullptr;

    return *this;
}

bool Texture::Create( const std::string& texture_file_path )
{
    if( texture_file_path.empty() )
    {
        CORE_LOG_ERROR("empty file_path string sent to create texture!");
        return false;
    }

    CORE_LOG_NORMAL(texture_file_path);

    int bpp; // bytes per pixel.
    m_data = stbi_load(texture_file_path.c_str(),&m_width,&m_height,&bpp,0);

    TextureFormat format = TextureFormat::INVALID;

    if( bpp == 3 )
        format = TextureFormat::RGB;

    else if( bpp == 4 )
        format = TextureFormat::RGBA;

    if( !m_data )
    {
        CORE_LOG_ERROR("file that was given to create texture is empty!\n");
        return false;
    }

    return Create(m_type,m_width,m_height,m_data,format);
}

bool Texture::Create( TextureType type, GLint width, GLint height, unsigned char* data, TextureFormat format )
{
    bool currect_data_passed = true;

    if( !width )
    {
        CORE_LOG_ERROR("cannot create a 2D texture with a width of 0!");
        currect_data_passed = false;
    }

    if( !height )
    {
        CORE_LOG_ERROR("cannot create a 2D texture with a height of 0!");
        currect_data_passed = false;
    }

    if( !data )
    {
        CORE_LOG_ERROR("cannot create a 2D texture without a data!");
        currect_data_passed = false;
    }

    if( !currect_data_passed )
        return false;

    m_type = type;
    m_format = format;
    m_width = width;
    m_height = height;
    m_data = data;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1,&m_id);

    //TextureManager::Get().UseTexture(m_id);
    
    Bind();

    glTexParameteri(GetGLTextureType(m_type), GL_TEXTURE_WRAP_S, GetGLTextureWrap(m_wrap_method));
    glTexParameteri(GetGLTextureType(m_type), GL_TEXTURE_WRAP_T, GetGLTextureWrap(m_wrap_method));
    glTexParameteri(GetGLTextureType(m_type), GL_TEXTURE_MIN_FILTER, GetGLTextureFilter(m_filter_method));
    glTexParameteri(GetGLTextureType(m_type), GL_TEXTURE_MAG_FILTER, GetGLTextureFilter(m_filter_method));

    glTexImage2D(GL_TEXTURE_2D, 0, GetGLTextureFormat(m_format),m_width,m_height,0,
                GetGLTextureFormat(m_format),GL_UNSIGNED_BYTE,m_data);

    Bind(false);

    return true;
}

Texture::operator bool() const
{
    return m_data != nullptr;
}

bool Texture::operator!() const
{
    return m_data == nullptr;
}

void Texture::Bind( bool bind )
{
    if( bind && !m_is_bound )
    {
        glBindTexture(GL_TEXTURE_2D,m_id);
        m_is_bound = true;
    }

    else if( !bind && m_is_bound )
    {
        glBindTexture(GL_TEXTURE_2D,0);
        m_is_bound = false;
    }
}
