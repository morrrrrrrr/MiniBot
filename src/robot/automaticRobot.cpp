#include "robot/automaticRobot.h"


RobPosition lerp(const RobPosition& a, const RobPosition& b, float t)
{
    return RobPosition{
        .point = (b.point - a.point) * t + a.point,
        .angle = (b.angle - a.angle) * t + a.angle
    };
}



AutomaticRobot::AutomaticRobot(RobotBase& robotBase) :
    m_base(robotBase)
{

}

void AutomaticRobot::update(int delta)
{
    checkForNewCommand();
    updateCurrentCommand(delta);
}

void AutomaticRobot::checkForNewCommand()
{
    if (m_commandActive) return;
    if (m_commandQueue.getSize() == 0) return;

    startCommand(m_commandQueue.pop_front());
}

void AutomaticRobot::updateCurrentCommand(int delta)
{
    if (!m_commandActive) return;

    switch (m_currentCommand.moveType)
    {
    case MoveType::Linear:
        m_commandActive = !handleLinearMove(m_currentCommand, delta);
        break;

    case MoveType::Optimal:
        m_commandActive = !handleOptimalMove(m_currentCommand, delta);
        break;

    default:
        m_commandActive = false;
        break;
    }
}

bool AutomaticRobot::handleLinearMove(RobCommand& command, int delta)
{
    float distance = (m_linearStart.point - command.target.point).magnitude();
    uint16_t time = distance / command.speed * 1000;

    m_commandProgress += delta;

    // "instantly" move in micro steps along a linear path from start to end
    m_base.setPosition(lerp(m_linearStart, command.target, static_cast<float>(m_commandProgress) / time), 0);

    return m_commandProgress >= time;
}
bool AutomaticRobot::handleOptimalMove(RobCommand& command, int delta)
{
    return !m_base.isMoving();
}

void AutomaticRobot::startCommand(RobCommand command)
{
    m_currentCommand = command;
    m_commandActive = true;
    m_commandProgress = 0;

    switch (command.moveType)
    {
    case MoveType::Linear:
        m_linearStart = m_base.getCurrentPosition();
        break;

    case MoveType::Optimal:
        m_base.setPosition(command.target, command.speed);
        break;

    default:
        m_commandActive = false;
        break;
    }
}
