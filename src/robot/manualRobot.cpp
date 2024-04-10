#include "robot/manualRobot.h"

ManualRobot::ManualRobot(RobotBase& base, CommandExecutor& commandExecutor) :
    m_base(base), m_executor(commandExecutor)
{ /* do nothing */ }

void ManualRobot::update(int delta)
{
    if (!m_executor.isCommandActive())
        m_executor.setCommand(m_input);
}


void ManualRobot::setInput(RobCommand input)
{
    m_input = input;
}
