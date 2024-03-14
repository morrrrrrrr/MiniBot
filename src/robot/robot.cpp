#include "robot/robot.h"

Robot::Robot() :
    m_mode(RobotMode::OFF),
    m_base(),
    m_automatic(m_base),
    m_manual(m_base)
{ /* do nothing */ }

void Robot::attach(const uint8_t pins[])
{
    m_base.attach(pins);
}
void Robot::attachRead(const uint8_t pins[])
{
    m_base.attachRead(pins);
}

void Robot::update()
{
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
}
