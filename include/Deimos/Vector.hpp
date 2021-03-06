
#ifndef DEIMOS_VECTOR_H_INCLUDED
#define DEIMOS_VECTOR_H_INCLUDED

namespace deimos
{
    template<class T>
    struct Vector2d
    {
        Vector2d():
            x(T()),
            y(T())
        {}

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
        a(T())
        {}

        T x, y, z, a; // a ?
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
}

#endif