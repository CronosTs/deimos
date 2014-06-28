#ifndef DEIMOS_MATRIX_H_INCLUDED
#define DEIMOS_MATRIX_H_INCLUDED


#include <Phobos/Exception.h>
#include <Phobos/BaseAPI.h>

#include <array>
#include <cmath>

namespace Deimos
{
    //TODO: implement common matrix operations
    template<class T, int Line, int Column>
    class Matrix
    {
        //this class is needed to use the "[][]" sintax on this class
        class Proxy
        {
            public:

                Proxy(std::array<T, Line*Column>& array, int columns, int currentLine):
                    m_columns(columns),
                    m_currentLine(currentLine),
                    m_array(array)
                {}

                ~Proxy()
                {}

                T&  operator [] (int column)
                {
                    return m_array[m_columns*m_currentLine + column];
                }

            private:

                int m_columns,
                    m_currentLine;
                std::array<T, Line*Column>& m_array;
        };

        public:

            Matrix()
            {
                for (int i = 0; i < Line; i++)
                    for (int j = 0; j < Column; j++)
                    {
                        if (Line == Column && i == j)
                            (*this)[i][j] = 1;
                        else
                            (*this)[i][j] = 0;
                    }
            }

            ~Matrix()
            {}

            Proxy operator [] (int line)
            {
                return Proxy(m_matrix, Column, line);
            }

            T At(int line, int column) const
            {
                return m_matrix[line*Column + column];
            }

            Matrix<T, Column, Line> Traspose() const
            {
                Matrix<T, Column, Line> tmpMatrix;
                for (int i = 0; i < Line; i++)
                    for (int j = 0; j < Column; j++)
                        tmpMatrix[j][i] = At(i, j);

                    return tmpMatrix;
            }

            template <class I, int L, int C>
            Matrix<I, Line, C> operator * (const Matrix<I, L, C>& matrix) const
            {
                if (Column != L)
                    PH_RAISE(Phobos::INVALID_PARAMETER_EXCEPTION, "Core", "Invalid Matrix!");

                Matrix<I, Line, C> tmpMatrix;
                for (int i = 0; i < Line; i++)
                    for (int j = 0; j < C; j++)
                    {
                        float tmp = 0;
                        for (int c = 0; c < Column; c++) //Or Column or L, because both has the same value
                            tmp += At(i, c) * matrix.At(c, j);

                        tmpMatrix[j][i] = tmp;
                    }

                return tmpMatrix;
            }

            template <class I, int L, int C>
            Matrix<I, L, C> operator + (const Matrix<I, L, C>& matrix) const
            {
                if (Column != C || Line != L)
                    PH_RAISE(Phobos::INVALID_PARAMETER_EXCEPTION, "Core", "Invalid Matrix!");

                Matrix<I, L, C> tmpMatrix;
                for (int i = 0; i < Line; i++)
                    for (int j = 0; j < Column; j++)
                        tmpMatrix[j][i] = At(i, j) + matrix.At(i, j);

                return tmpMatrix;
            }

            Matrix operator * (float scalar) const
            {
                Matrix tmpMatrix;
                for (int i = 0; i < Line; i++)
                    for (int j = 0; j < Column; j++)
                        tmpMatrix[j][i] = At(i, j) * scalar;

                return tmpMatrix;
            }

        private:

            std::array<T, Line*Column> m_matrix;
    };

    typedef Matrix<float, 4, 4> fmat4;
    typedef Matrix<float, 4, 3> fmat43;

    typedef Matrix<int, 4, 4> imat4;
    typedef Matrix<int, 4, 3> imat43;

    fmat4 ScalingMatrix(float x, float y, float z);

    fmat4 TranslationMatrix(float x, float y, float z);

    //Observation: this rotation amtrix are in opengl left-hand mode!
    fmat4 XRotationMatrix(float angle);
    fmat4 YRotationMatrix(float angle);
    fmat4 ZRotationMatrix(float angle);
}

#endif