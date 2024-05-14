#include "robot/manualRobot.h"

ManualRobot::ManualRobot(RobotBase& base, CommandExecutor& commandExecutor) :
    m_base(base), m_executor(commandExecutor)
{ /* do nothing */ }

void ManualRobot::update(int delta)
{
    
}


void ManualRobot::setInput(RobCommand input)
{
    m_executor.setCommand(input);
}
