#include "robot/robot.h"

Robot::Robot(const Mat4& axisLengths) :
    m_mode(RobotMode::OFF),
    m_base(axisLengths),
    m_executor(m_base),
    m_automatic(m_base, m_executor),
    m_manual(m_base, m_executor)
{ /* do nothing */ }

void Robot::attach(const uint8_t pins[])
{
    m_base.attach(pins);
}
void Robot::attachRead(const uint8_t pins[])
{
    m_base.attachRead(pins);
}

void Robot::setServoOffsets(float s0, float s1, float s2, float s3)
{
    getBase().m_servoOffsets.a = s0;
    getBase().m_servoOffsets.b = s1;
    getBase().m_servoOffsets.c = s2;
    getBase().m_servoOffsets.d = s3;
}
void Robot::setServoOffset(int index, float offset)
{
    getBase().m_servoOffsets.set(index, offset);
}

void Robot::update()
{
    // check for any errors, only if there are none, continue
    if (check_robot_error())
    {
        Serial.println("There was a robot error!");
        Serial.print("Error Code: "); Serial.println(robError);
        
        m_mode = RobotMode::OFF;
    }

    m_time.update();

    switch (m_mode)
    {
    case RobotMode::AUTOMATIC:
        m_automatic.update(m_time.getDelta());
        break;

    case RobotMode::MANUAL:
        m_manual.update(m_time.getDelta());
        break;

    default:
        break;
    }

    m_executor.update(m_time.getDelta());
}

void Robot::changeMode(RobotMode mode)
{
    m_mode = mode;
}

AutomaticRobot& Robot::getAutomatic()
{
    return m_automatic;
}
ManualRobot& Robot::getManual()
{
    return m_manual;
}
RobotBase& Robot::getBase()
{
    return m_base;
}
CommandExecutor& Robot::getExecutor()
{
    return m_executor;
}
