
#ifndef __INVERSE_KINEMATIC_H__
#define __INVERSE_KINEMATIC_H__

#include "common.h"
#include "vector.h"
#include "robError.h"

struct Mat4
{
public:
    Mat4() :
        a(0), b(0), c(0), d(0)
    {

    }
    Mat4(float a, float b, float c, float d) :
        a(a), b(b), c(c), d(d)
    {

    }

public:
    float a, b, c, d;
};
struct RobPosition
{
    Vector3f point;
    float angle;
};

static inline RobPosition lerpRobPosition(const RobPosition& a, const RobPosition& b, float t)
{
    return RobPosition{
        .point = (b.point - a.point) * t + a.point,
        .angle = (b.angle - a.angle) * t + a.angle
    };
}

class InverseKinematic {
public:
    // Simple Constructor
    InverseKinematic()
    { }
    
    InverseKinematic(Mat4 axis_lengths) : 
        m_axis_lengths(axis_lengths)
    {  }

public:
    Mat4 calculate(const RobPosition& req)
    {
        // transform the 4-dimensional problem to 3 dimensions
        float angle = atan2f(req.point.z, req.point.x);

        float reqAngle = (req.angle - (static_cast<int>(req.angle / 360) * 360)) * M_PI / 180.0f;

        Vector3f point2d(
            /* x: */ sqrtf( SQUARE(req.point.x) + SQUARE(req.point.z) ),
            /* y: */ req.point.y 
        );

        Vector3f target2d = point2d + Vector3f(cosf(reqAngle), sinf(reqAngle)) * m_axis_lengths.c;

        Mat4 res;
        handle_robot_error(calculate3DIM(target2d, angle, res));

        // why? i dont know
        res.b = -res.b;

        res.d = reqAngle -res.b -res.c;

        return res;
    }

private:
    // Calculate the axis angles based on inverse kinematic 3 AXES
    rob_error_t calculate3DIM(const Vector3f& point2d, float angle, Mat4& out) const 
    {
        float l1 = m_axis_lengths.a;
        float l2 = m_axis_lengths.b;

        /*
         * Make a 3-dimensional reverse kinematic through the point and request thingy
         */
        
        float x = point2d.x;
        float y = point2d.y;

        float b =  atan2f(y, x); // Angle beta

        float a = acosf(
            (SQUARE(l1) + SQUARE(l2) - SQUARE(x) - SQUARE(y)) / (2*l1*l2)
        ); // Angle alpha between axises
        float p2 = M_PI - a;

        float psi = atan2f(l2 * sinf(p2), l1 + l2 * cosf(p2));
        float p1 = b + psi;

        out.a = angle;
        out.b = p1;
        out.c = p2;

        return rob_error_t::NO_ERROR;
    }

public:
    void setAxisLengths(Mat4 axisLengths)
    {
        m_axis_lengths = axisLengths;
    }

private:
    Mat4 m_axis_lengths;

};

#endif