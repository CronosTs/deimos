#include "Mesh.hpp"

#include "Renderer.hpp"
#include "GraphicDefs.hpp"

namespace  deimos
{
    Mesh::Mesh() :
        m_size(0)
    {}

    Mesh::Mesh(const std::vector<Vertex>& vertex):
        m_vertex(vertex),
        m_size(vertex.size())
    {}

    Mesh::~Mesh()
    {}

    void Mesh::Draw(int primitive, int offset, int count) const
    {
        if (count <= 0)
            count = m_vertex.size();

        if (offset < 0) //log a warning here
            offset = 0;

        if (m_vbo.HasCreated())
            Renderer::Draw(m_vbo, primitive, offset, count);
        else
            Renderer::Draw(m_vertex, primitive, offset, count);
    }

    void Mesh::CreateVertexBuffer(bool freeLocalContent)
    {
        if (m_vertex.empty()) //throw exception
            return;

        m_vbo.create(); //maybe this is redundant
        m_vbo.upload(m_vertex, VBOTarget::STATIC);

        if (freeLocalContent)
            m_vertex.resize(0);
    }

    void Mesh::SetVertexData(const std::vector<Vertex>& vertex)
    {
        m_vertex = vertex;
        m_size = m_vertex.size();
    }
}