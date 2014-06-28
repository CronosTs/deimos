#include "Sprite.hpp"

#include "GraphicDefs.hpp"

namespace Deimos
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

    void Sprite::SetVisible(bool visible)
    {
        m_visible = visible;
    }

    void Sprite::Draw()
    {
        if (!m_visible)
            return;

        m_texture->Bind();
        m_mesh.Draw(Primitives::TRIANGLES); //draw everything
    }

    void Sprite::SetRect(const FRect& rect)
    {
        float width  = m_texture->GetWidth(),
              height = m_texture->GetHeight();

        if (rect != FRect(0, 0, 0, 0))
            m_rect = rect;
        else
            m_rect = FRect(0, 0, width, height);

        Quads quad;
        quad.t1.position.x = 0;
        quad.t1.position.y = 0;
        quad.t1.texture.x  = rect.m_tOrigin[0]/width;
        quad.t1.texture.y  = rect.m_tOrigin[1]/height;
        
        quad.t2.position.x = width;
        quad.t2.position.y = 0;
        quad.t2.texture.x  = (rect.m_tOrigin[0]+rect.m_tSize.m_tWidth)/width;
        quad.t2.texture.y  = rect.m_tOrigin[1]/height;

        quad.t3.position.x = 0;
        quad.t3.position.y = height;
        quad.t3.texture.x  = rect.m_tOrigin[0]/width;
        quad.t3.texture.y  = (rect.m_tOrigin[1] + rect.m_tSize.m_tHeight) / height;

        quad.t4.position.x = width;
        quad.t4.position.y = height;
        quad.t4.texture.x  = (rect.m_tOrigin[0] + rect.m_tSize.m_tWidth) / width;
        quad.t4.texture.y  = (rect.m_tOrigin[1] + rect.m_tSize.m_tHeight) / height;

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
        m_mesh.GetBuffer().ConfigVertex(VBOConfig(2, VBODataType::FLOAT, sizeof(Vertex), 0));
        m_mesh.GetBuffer().ConfigTexture(VBOConfig(2, VBODataType::FLOAT, sizeof(Vertex), 8));
    }

    void Sprite::SetTexture(TexturePtr_t& texture, const FRect& rect)
    {
        using namespace Phobos;

        m_texture = texture;

        SetRect(rect);
    }  

    void Sprite::SetTexture(const Phobos::String_t& texture, const FRect& rect)
    {
        SetTexture(std::make_shared<Texture>(texture), rect);
    }

    Sprite::TexturePtr_t Sprite::GetTexture()
    {
        return m_texture;
    }
}