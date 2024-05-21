#include "robot/commandExecutor.h"

CommandExecutor::CommandExecutor(RobotBase& robotBase) : 
    m_base(robotBase), m_commandProgress(0)
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
    int time = distance / static_cast<float>(command.speed) * 1000;

    if (distance <= 0)
    {
        return true;
    }

    m_commandProgress += delta;

    float t = static_cast<float>(m_commandProgress) / time;

    if (m_commandProgress >= time) t = 1.0f;

    // Serial.print("t: "); Serial.println(t);

    RobPosition lerpedPos = lerpRobPosition(m_linearStart, command.target, t);

    // "instantly" move in micro steps along a linear path from start to end
    m_base.setPosition(lerpedPos, 0);

    return m_commandProgress >= time;
}
bool CommandExecutor::handleOptimalMove(RobCommand& command, int delta)
{
    return millis() - m_optimalStart >= m_optimalTime && !m_base.isMoving();
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
        m_optimalTime = m_base.setPosition(command.target, command.speed);
        m_optimalStart = millis();

        Serial.println("Starting Optimal Move:");
        Serial.print("Time: "); Serial.println(m_optimalTime);
        break;

    default:
        m_commandActive = false;
        break;
    }
}
