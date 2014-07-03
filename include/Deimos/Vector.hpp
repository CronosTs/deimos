
#ifndef DEIMOS_VECTOR_H_INCLUDED
#define DEIMOS_VECTOR_H_INCLUDED

namespace Deimos
{
    template<class T>
    struct Vector2d
    {
        Vector2d():
            x(T()),
            y(T())
        {}

        Vector2d(T _x, T _y) :
            x(_x),
            y(_y)
        {}

        void operator += (const Vector2d& other)
        {
            x += other.x;
            y += other.y;
        }

        void operator -= (const Vector2d& other)
        {
            x -= other.x;
            y -= other.y;
        }

        Vector2d operator + (const Vector2d& other)
        {
            return Vector2d(x + other.x, y + other.y);
        }

        Vector2d operator - (const Vector2d& other)
        {
            return Vector2d(x - other.x, y - other.y);
        }

        T x, y;
    };

    template<class T>
    struct Vector3d
    {
        Vector3d() :
        x(T()),
        y(T()),
        z(T())
        {}

        T x, y, z;
    };

    template<class T>
    struct Vector4d
    {
        Vector4d() :
        x(T()),
        y(T()),
        z(T()),
        w(T())
        {}

        T x, y, z, w; // a ?
    };

    typedef Vector2d<float> fvec2;
    typedef Vector3d<float> fvec3;
    typedef Vector4d<float> fvec4;

    typedef Vector2d<double> dvec2;
    typedef Vector3d<double> dvec3;
    typedef Vector4d<double> dvec4;

    typedef Vector2d<int> ivec2;
    typedef Vector3d<int> ivec3;
    typedef Vector4d<int> ivec4;

    typedef Vector2d<unsigned char> ubvec2;
    typedef Vector3d<unsigned char> ubvec3;
    typedef Vector4d<unsigned char> ubvec4;
}

#endif