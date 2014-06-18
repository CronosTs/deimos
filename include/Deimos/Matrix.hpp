#ifndef DEIMOS_MATRIX_H_INCLUDED
#define DEIMOS_MATRIX_H_INCLUDED

#include <array>

namespace deimos
{
    //TODO: implement common matrix operations
    template<class T, int Line, int Column>
    class Matrix
    {
        public:

            Matrix()
            {
                if (line != column)
                    return;
                
                for (int i = 0; i < Line; i++)
                    At(i, i) = 1;
            }

            ~Matrix()
            {}

            T& operator [] (int element)
            {
                return m_matrix[element];
            }

            T& At(int line, int column)
            {
                return m_matrix[line*Column + column];
            }

        private:

            std::array<T, Line*Column> m_matrix;
    };

    typedef Matrix<float, 4, 4> fmat4;
    typedef Matrix<float, 4, 3> fmat43;

    typedef Matrix<int, 4, 4> imat4;
    typedef Matrix<int, 4, 3> imat43;
}

#endif