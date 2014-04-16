#include "Texture.hpp"

#include <SDL.h>
#include <GL/glew.h>
#include <Phobos/Exception.h>

namespace deimos
{
    Texture::Texture():
        m_created(false),
        m_id(0),
        m_width(0),
        m_height(0)
    {}

    Texture::Texture(const Phobos::String_t& file)
    {
        loadFromFile(file);
    }

    Texture::~Texture()
    {
        destroy();
    }

    void Texture::loadFromFile(const Phobos::String_t& file)
    {
        if (m_created)
            destroy();

        
        SDL_Surface* image = SDL_LoadBMP(file.c_str());
        if (!image)
            PH_RAISE(Phobos::ExceptionTypes::NATIVE_API_FAILED_EXCEPTION,
                     "Texture",
                     Phobos::String_t("Cound not load this file: ")+file);

        ::glGenTextures(GL_TEXTURE_2D, &m_id);
        ::glBindTexture(GL_TEXTURE_2D, m_id);

        //Ponto V rules
        int format = image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

        ::glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 
                       0, format, GL_UNSIGNED_BYTE, image->pixels);

        m_created = true;
        m_width   = image->w;
        m_height  = image->h;

        //memory leak if throws ??
        SDL_FreeSurface(image);

        ::glEnable(GL_TEXTURE_2D);
    }

    void Texture::bind()
    {
        if (!m_created)
            return;

        ::glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::destroy()
    {
        if (!m_created)
            return;

        ::glDeleteTextures(GL_TEXTURE_2D, &m_id);
        m_created = false;
        m_id = 0;
    }

    unsigned int Texture::getWidth()
    {
        return m_width;
    }

    unsigned int Texture::getHeight()
    {
        return m_height;
    }
}