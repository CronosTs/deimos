#include "Sprite.hpp"

#include "GraphicDefs.hpp"

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
        if (!m_visible)
            return;

        m_texture->bind();
        m_mesh.Draw(Primitives::TRIANGLES); //draw everything
    }

    void Sprite::setRect(const FRect& rect)
    {
        m_rect = rect;

        Quads quad;
        quad.t1.position.x = 0;
        quad.t1.position.y = 0;
        quad.t1.texture.x  = 0;
        quad.t1.texture.y  = 0;
        
        quad.t2.position.x = rect.m_tSize.m_tWidth;
        quad.t2.position.y = 0;
        quad.t2.texture.x  = 1;
        quad.t2.texture.y  = 0;

        quad.t3.position.x = 0;
        quad.t3.position.y = rect.m_tSize.m_tHeight;
        quad.t3.texture.x  = 0;
        quad.t3.texture.y  = 1;

        quad.t4.position.x = rect.m_tSize.m_tWidth;
        quad.t4.position.y = rect.m_tSize.m_tHeight;
        quad.t4.texture.x  = 1;
        quad.t4.texture.y  = 1;

        std::vector<Vertex> data;
        //first triangle
        data.push_back(quad.t1);
        data.push_back(quad.t3);
        data.push_back(quad.t4);
        //second triangle
        data.push_back(quad.t1);
        data.push_back(quad.t4);
        data.push_back(quad.t2);

        m_mesh.SetVertexData(data);
        m_mesh.CreateVertexBuffer(true); //don't work
        //m_mesh.GetBuffer().configVertex(VBOConfig(2, VBODataType::FLOAT, sizeof(Vertex), 0));
        //m_mesh.GetBuffer().configTexture(VBOConfig(2, VBODataType::FLOAT, sizeof(Vertex), 8));
    }

    void Sprite::setTexture(TexturePtr_t& texture)
    {
        using namespace Phobos;

        m_texture = texture;
        Float_t width = static_cast<Float_t>(texture->getWidth());
        Float_t height = static_cast<Float_t>(texture->getHeight());

        setRect(FRect(0, 0, Size_s<Float_t>(width, height)));
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