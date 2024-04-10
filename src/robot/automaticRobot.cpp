#include "robot/automaticRobot.h"

AutomaticRobot::AutomaticRobot(RobotBase& robotBase, CommandExecutor& commandExecutor) :
    m_base(robotBase), m_executor(commandExecutor)
{ /* do nothing */ }

void AutomaticRobot::update(int delta)
{
    checkForNewCommand();
}

void AutomaticRobot::checkForNewCommand()
{
    if (m_running) return;
    if (m_executor.isCommandActive()) return;
    if (m_program.size() == 0) return;

    m_executor.setCommand(*m_program.current());
    m_program.step();
}
