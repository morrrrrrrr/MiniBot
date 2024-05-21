#include "robot/robotBase.h"

RobotBase::RobotBase(const Mat4& axisLengths) :
    m_servos({
        Servo(0),
        Servo(1),
        Servo(2),
        Servo(3)
    }),
    m_inverseKinematic(axisLengths)
{

}

void RobotBase::attach(const uint8_t pins[])
{
    Servo* servo;
    const uint8_t* pin;

    for (servo = m_servos, pin = pins; servo - m_servos < 4; servo++, pin++)
    {
        servo->attach(*pin);
    }
}
void RobotBase::attachRead(const uint8_t pins[])
{
    Servo* servo;
    const uint8_t* pin;

    for (servo = m_servos, pin = pins; servo - m_servos < 4; servo++, pin++)
    {
        servo->attachRead(*pin);
    }
}

void writeResult(Servo* servos, Mat4& angles, Mat4& offsets, uint16_t time, float angleLimit)
{
    if (robError) return;

    float finalAngles[4];

    finalAngles[0] = (angles.a + offsets.a);
    finalAngles[1] = (angles.b + offsets.b);
    finalAngles[2] = (angles.c + offsets.c);
    finalAngles[3] = (angles.d + offsets.d);

    for (int i = 0; i < 4; i++)
    {
        // if (finalAngles[i] < angleLimit)
        // {
        //     handle_robot_error(rob_error_t::TOO_CLOSE_ANGLES);
        //     return;
        // }

        servos[i].write(finalAngles[i], time);

        // Debug Message for servo angles
        // Serial.print("Servo ");
        // Serial.print(i);
        // Serial.print(" moved to angle ");
        // Serial.println(finalAngles[i]);
        
        Serial.print(i);
        Serial.print(";");
        Serial.println(finalAngles[i]);
    }
}

uint16_t RobotBase::setPosition(RobPosition pos, uint16_t speed)
{ 
    Mat4 res = m_inverseKinematic.calculate(pos);

    uint16_t time = 0;
    if (speed)
    {
        time = speedToTime(m_position, pos, speed);
    }

    m_position = pos;

    writeResult(m_servos, res, m_servoOffsets, time, m_angleLimit);

    return time;
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

Servo* RobotBase::getServos()
{
    return m_servos;
}

void RobotBase::setAxisLengths(float ax0, float ax1, float ax2)
{
    m_inverseKinematic.setAxisLengths({ax0, ax1, ax2, 0});
}
