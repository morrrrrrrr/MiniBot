
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "common.h"

struct Vector3f
{
public:
    Vector3f();
    Vector3f(float x, float y, float z = 0.0f);
    Vector3f(const Vector3f& other);
    virtual ~Vector3f();

public:
    /*
     * Returns the squared magnitude of the vector
     */
    float sq_magnitude() const;
    /*
     * Returns the magnitude of the vector
     */
    float magnitude() const;

    /*
     * Returns a normalized (mag = 1.0f) vector
     */
    Vector3f normalized() const;

public:
    float x, y, z;
};

Vector3f operator+(const Vector3f& a, const Vector3f& b);
Vector3f operator-(const Vector3f& a, const Vector3f& b);
Vector3f operator*(const Vector3f& a, float f);
Vector3f operator/(const Vector3f& a, float f);

Vector3f& operator+=(Vector3f& a, const Vector3f& b);
Vector3f& operator-=(Vector3f& a, const Vector3f& b);
Vector3f& operator*=(Vector3f& a, float f);
Vector3f& operator/=(Vector3f& a, float f);

float dot(const Vector3f& a, const Vector3f& b);
Vector3f cross(const Vector3f& a, const Vector3f& b);

// define a ostream operator overload when run in cmd
#ifdef WIN

std::ostream& operator<<(std::ostream& os, const Vector3f& vec);

#endif

#endif