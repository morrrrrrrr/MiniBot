#include "robot/manualRobot.h"

ManualRobot::ManualRobot(RobotBase& base) :
    m_base(base)
{

}

void ManualRobot::update(int delta)
{
    const float factor = delta * m_speed;

    RobPosition offset = 
    {
        .point = m_input.point * factor,
        .angle = m_input.angle * factor
    };

    RobPosition nextPosition = {
        .point = m_base.getCurrentPosition().point + offset.point,
        .angle = m_base.getCurrentPosition().angle + offset.angle
    };

    // "instantly" move to the next position
    m_base.setPosition(nextPosition, 0);
}


void ManualRobot::setInput(RobPosition input)
{
    m_input = input;
}
void ManualRobot::setSpeed(uint16_t speed)
{
    m_speed = speed;
}
