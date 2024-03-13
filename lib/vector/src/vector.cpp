#include "vector.h"
/*
 * Vector implenetation bla bla bla
 */

#include "common.h"

/*
 * Constructors
 */

Vector3f::Vector3f() :
    x(0.0f), y(0.0f), z(0.0f)
{ /* do nothing */}

Vector3f::Vector3f(float x, float y, float z) :
    x(x), y(y), z(z)
{ /* do nothing */}

Vector3f::Vector3f(const Vector3f& other) :
    x(other.x), y(other.y), z(other.z)
{ /* do nothing */}

Vector3f::~Vector3f()
{ /* do nothing */}

/*
 * Const Helper functions
 */

float Vector3f::sq_magnitude() const
{
    return x*x + y*y + z*z;
}

float Vector3f::magnitude() const
{
    return sqrtf( this->sq_magnitude() );
}

Vector3f Vector3f::normalized() const
{
    return (*this) / this->magnitude();
}

/*
 * Non-Modifying Vector operators
 */

Vector3f operator+(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(
        /* x: */ a.x + b.x,
        /* y: */ a.y + b.y,
        /* z: */ a.z + b.z
        );
}
Vector3f operator-(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(
        /* x: */ a.x - b.x,
        /* y: */ a.y - b.y,
        /* z: */ a.z - b.z
        );
}
Vector3f operator*(const Vector3f& a, float f)
{
    return Vector3f(
        /* x: */ a.x * f,
        /* y: */ a.y * f,
        /* z: */ a.z * f
        );
}
Vector3f operator/(const Vector3f& a, float f)
{
    return Vector3f(
        /* x: */ a.x / f,
        /* y: */ a.y / f,
        /* z: */ a.z / f
        );
}

/*
 * Mofifying Vector operators
 */

Vector3f& operator+=(Vector3f& a, const Vector3f& b)
{
    a = a + b;
    return a;
}
Vector3f& operator-=(Vector3f& a, const Vector3f& b)
{
    a = a - b;
    return a;
}
Vector3f& operator*=(Vector3f& a, float f)
{
    a = a * f;
    return a;
}
Vector3f& operator/=(Vector3f& a, float f)
{
    a = a / f;
    return a;
}

/*
 * Extra vector operations
 */

float dot(const Vector3f& a, const Vector3f& b)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z;
}

Vector3f cross(const Vector3f& a, const Vector3f& b)
{
    return Vector3f(
        /* x: */ a.y*b.z - a.z*b.y,
        /* y: */ a.z*b.x - a.x*b.z,
        /* z: */ a.x*b.y - a.y*b.x
        );
}

#ifdef WIN

std::ostream& operator<<(std::ostream& os, const Vector3f& vec)
{
    os << vec.x << ", " << vec.y << ", " << vec.z;
    return os;
}

#endif
