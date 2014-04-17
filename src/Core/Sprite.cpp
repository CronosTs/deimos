#include "Sprite.hpp"

namespace deimos
{
    Sprite::Sprite():
        m_visible(true)
    {
        //empty
    }

    Sprite::~Sprite()
    {
         //empty
    }

    void Sprite::setVisible(bool visible)
    {
        m_visible = visible;
    }

    void Sprite::draw()
    {
        m_texture->bind();
        m_vbo.draw(VBODrawMode::TRIANGLE, 0, 2);
    }

    void Sprite::setRect(const FRect& rect)
    {
        m_rect = rect;

        Quads quad;
        quad.t1.position.x = 0;
        quad.t1.position.y = 0;
        quad.t1.texture.x  = rect.m_tOrigin[0];
        quad.t1.texture.y  = rect.m_tOrigin[1];
        
        quad.t2.position.x = rect.m_tSize.m_tWidth;
        quad.t2.position.y = 0;
        quad.t2.texture.x  = rect.m_tOrigin[0] + rect.m_tSize.m_tWidth;
        quad.t2.texture.y  = rect.m_tOrigin[1];

        quad.t3.position.x = 0;
        quad.t3.position.y = rect.m_tSize.m_tHeight;
        quad.t3.texture.x  = rect.m_tOrigin[0];
        quad.t3.texture.y  = rect.m_tOrigin[1] + rect.m_tSize.m_tHeight;

        quad.t4.position.x = rect.m_tSize.m_tWidth;
        quad.t4.position.y = rect.m_tSize.m_tHeight;
        quad.t4.texture.x  = rect.m_tOrigin[0] + rect.m_tSize.m_tWidth;
        quad.t4.texture.y  = rect.m_tOrigin[1] + rect.m_tSize.m_tHeight;

        VBO<Vertex>::VBOData data;
        //first triangle
        data.push_back(quad.t1);
        data.push_back(quad.t3);
        data.push_back(quad.t4);
        //second triangle
        data.push_back(quad.t1);
        data.push_back(quad.t4);
        data.push_back(quad.t2);

        m_vbo.upload(data, VBOTarget::STATIC);
        m_vbo.configVertex(VBOConfig(2, VBODataType::FLOAT, sizeof(Vertex), 0));
        m_vbo.configTexture(VBOConfig(2, VBODataType::FLOAT, sizeof(Vertex), 8));
        m_vbo.free(); //destroy the local copy
    }

    void Sprite::setTexture(TexturePtr_t& texture)
    {
        using namespace Phobos;
        m_texture = texture;
        setRect(FRect(0, 0, Size_s<Float32_t>(texture->getWidth(), texture->getHeight())));
    }

    void Sprite::setTexture(const Phobos::String_t& texture)
    {
        setTexture(std::make_shared<Texture>(texture));
    }

    Sprite::TexturePtr_t Sprite::getTexture()
    {
        return m_texture;
    }
}