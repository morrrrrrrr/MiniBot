#include "robot/robotBase.h"

RobotBase::RobotBase() :
    m_servos({
        Servo(0),
        Servo(1),
        Servo(2),
        Servo(3)
    })
{

}

void RobotBase::attach(uint8_t pins[])
{
    Servo* servo;
    uint8_t* pin;

    for (servo = m_servos, pin = pins; servo - m_servos < 4; servo++, pin++)
    {
        servo->attach(*pin);
    }
}
void RobotBase::attachRead(uint8_t pins[])
{
    Servo* servo;
    uint8_t* pin;

    for (servo = m_servos, pin = pins; servo - m_servos < 4; servo++, pin++)
    {
        servo->attachRead(*pin);
    }
}

void writeResult(Servo* servos, Mat4& angles, Mat4& offsets, uint16_t time)
{
    servos[0].write(angles.a + offsets.a, time);
    servos[1].write(angles.b + offsets.b, time);
    servos[2].write(angles.c + offsets.c, time);
    servos[3].write(angles.d + offsets.d, time);
}

void RobotBase::setPosition(RobPosition pos, uint16_t speed)
{
    Mat4 res = m_inverseKinematic.calculate(pos);

    uint16_t time = 0;
    if (speed)
    {
        time = speedToTime(m_position, pos, speed);
    }
    
    writeResult(m_servos, res, m_servoOffsets, time);
}

bool RobotBase::isMoving() const
{
    return
        m_servos[0].isMoving() || 
        m_servos[1].isMoving() || 
        m_servos[2].isMoving() || 
        m_servos[3].isMoving();
}

uint16_t RobotBase::speedToTime(RobPosition& current, RobPosition& next, uint16_t speed)
{
    Vector3f difference = next.point - current.point;

    return 
        difference.magnitude() // mm
        / speed // mm/s
        * 1000; // s to ms
}

RobPosition RobotBase::getCurrentPosition() const
{
    return m_position;
}
