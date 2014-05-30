
#ifndef DEIMOS_MESH_H_INCLUDED
#define DEIMOS_MESH_H_INCLUDED

#include "Vertex.hpp"
#include "VBO.hpp"
#include <vector>

namespace deimos
{
    class Mesh
    {
        public:

            Mesh();
            Mesh(const std::vector<Vertex>&);
            ~Mesh();
            void Draw(int=0, int=0) const;    //first is offset and the secont is the count

            //after create buffer if true is used then the client side vertex will be deleted
            void CreateVertexBuffer(bool=false); 
            void SetVertexData(const std::vector<Vertex>&);

            //inline ????
            inline const std::vector<Vertex>& GetVertexData()
            {
                return m_vertex;
            }

        private:

            std::vector<Vertex> m_vertex;
            VBO m_vbo;
    };
}

#endif