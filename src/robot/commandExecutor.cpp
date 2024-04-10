#include "robot/commandExecutor.h"

CommandExecutor::CommandExecutor(RobotBase& robotBase) : 
    m_base(robotBase)
{ /* do nothing */ }

void CommandExecutor::update(int delta)
{
    updateCurrentCommand(delta);
}

void CommandExecutor::setCommand(const RobCommand& cmd)
{
    if (isCommandActive()) return;

    startCommand(cmd);
}

bool CommandExecutor::isCommandActive()
{
    return m_commandActive;
}

void CommandExecutor::updateCurrentCommand(int delta)
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

bool CommandExecutor::handleLinearMove(RobCommand& command, int delta)
{
    float distance = (m_linearStart.point - command.target.point).magnitude();
    uint16_t time = distance / command.speed * 1000;

    m_commandProgress += delta;

    // "instantly" move in micro steps along a linear path from start to end
    m_base.setPosition(lerpRobPosition(m_linearStart, command.target, static_cast<float>(m_commandProgress) / time), 0);

    return m_commandProgress >= time;
}
bool CommandExecutor::handleOptimalMove(RobCommand& command, int delta)
{
    return !m_base.isMoving();
}

void CommandExecutor::startCommand(const RobCommand& command)
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