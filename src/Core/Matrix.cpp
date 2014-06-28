#include "Matrix.hpp"

namespace Deimos
{
    fmat4 ScalingMatrix(float x, float y, float z)
    {
        fmat4 matrix;
        matrix[0][0] = x;
        matrix[1][1] = y;
        matrix[2][2] = z;

        return matrix;
    }

    fmat4 TranslationMatrix(float x, float y, float z)
    {
        fmat4 matrix;
        matrix[0][3] = x;
        matrix[1][3] = y;
        matrix[2][3] = z;

        return matrix;
    }

    //Observation: this rotation amtrix are in opengl left-hand mode!
    fmat4 XRotationMatrix(float angle)
    {
        fmat4 matrix;
        matrix[1][1] = ::cos(angle);
        matrix[1][2] = ::sin(angle);
        matrix[2][1] = -::sin(angle);
        matrix[2][2] = ::cos(angle);
        return matrix;
    }

    fmat4 YRotationMatrix(float angle)
    {
        fmat4 matrix;
        matrix[0][0] = ::cos(angle);
        matrix[0][2] = -::sin(angle);
        matrix[2][0] = ::sin(angle);
        matrix[2][2] = ::cos(angle);
        return matrix;
    }

    fmat4 ZRotationMatrix(float angle)
    {
        fmat4 matrix;
        matrix[0][0] = ::cos(angle);
        matrix[0][1] = ::sin(angle);
        matrix[1][0] = -::sin(angle);
        matrix[1][1] = ::cos(angle);
        return matrix;
    }
}