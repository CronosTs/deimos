#include "Mesh.hpp"

#include "Renderer.hpp"

namespace  deimos
{
    Mesh::Mesh()
    {}

    Mesh::Mesh(const std::vector<Vertex>& vertex):
        m_vertex(vertex)
    {}

    Mesh::~Mesh()
    {}

    void Mesh::Draw(int offset, int count) const
    {
        if (count <= 0)
            count = m_vertex.size();

        if (offset < 0) //log a warning here
            offset = 0;

        if (m_vbo.HasCreated())
            Renderer::Draw(m_vbo, 0, offset, count);
        else
            Renderer::Draw(m_vertex, 0, offset, count);
    }

    void Mesh::CreateVertexBuffer(bool freeLocalContent)
    {
        if (m_vertex.empty()) //throw exception
            return;

        m_vbo.create(); //maybe this is redundant
        m_vbo.upload(m_vertex, VBOTarget::STATIC); //VBO is duplicating data!!!!

        if (freeLocalContent)
            m_vertex.resize(0);
    }

    void Mesh::SetVertexData(const std::vector<Vertex>& vertex)
    {
        m_vertex = vertex;
    }
}