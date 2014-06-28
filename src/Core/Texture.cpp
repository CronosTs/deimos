#include "Texture.hpp"

#include <SDL.h>
#include <SDL_Image.h>
#include <GL/glew.h>
#include <Phobos/Exception.h>
#include <Phobos/Log.h>
#include <OpenglErrorChecker.hpp>

namespace Deimos
{
    Texture::Texture():
        m_created(false),
        m_id(0),
        m_width(0),
        m_height(0)
    {}

    Texture::Texture(const Phobos::String_t& file)
    {
        LoadFromFile(file);
    }

    Texture::~Texture()
    {
        Destroy();
    }

    void Texture::LoadFromFile(const Phobos::String_t& file)
    {
        if (m_created)
            Destroy();
        
        SDL_Surface* image = IMG_Load(file.c_str());
        if (image == nullptr)
            PH_RAISE(Phobos::ExceptionTypes::NATIVE_API_FAILED_EXCEPTION,
            "Texture",
            Phobos::String_t("Could not load this file: ")
                .append(file)
                .append("; SDL_Image_Error: ")
                .append(IMG_GetError()));

        DEIMOS_GL_CHECK(::glGenTextures(1, &m_id));
        DEIMOS_GL_CHECK(::glBindTexture(GL_TEXTURE_2D, m_id));

        /*
            Is mipmapping being used?

                YES: Supply all mipmap layers – optimally set glTexParameteri 
                GL_TEXTURE_BASE_LEVEL and GL_TEXTURE_MAX_LEVEL, as well as 
                GL_TEXTURE_MIN_LOD and GL_TEXTURE_MAX_LOG.

                NO: Turn off mipmap filtering by setting glTexParameteri 
                GL_TEXTURE_MIN_FILTER to GL_NEAREST or GL_LINEAR.

                By: http://stackoverflow.com/questions/13867219/opengl-renders-texture-all-white

        */

        DEIMOS_GL_CHECK(::glTexParameteri(GL_TEXTURE_2D, 
            GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        
        //Ponto V rules
        int format = image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

        DEIMOS_GL_CHECK(::glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h,
                       0, format, GL_UNSIGNED_BYTE, image->pixels));

        m_created = true;
        m_width   = image->w;
        m_height  = image->h;

        //memory leak if throws ??
        ::SDL_FreeSurface(image);

        DEIMOS_GL_CHECK(::glEnable(GL_TEXTURE_2D));
    }

    void Texture::Bind()
    {
        if (!m_created)
            return;

        DEIMOS_GL_CHECK(::glBindTexture(GL_TEXTURE_2D, m_id));
    }

    void Texture::Destroy()
    {
        if (!m_created)
            return;

        DEIMOS_GL_CHECK(::glDeleteTextures(1, &m_id));
        m_created = false;
        m_id = 0;
    }

    unsigned int Texture::GetWidth()
    {
        return m_width;
    }

    unsigned int Texture::GetHeight()
    {
        return m_height;
    }
}