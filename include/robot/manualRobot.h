
#ifndef __MANUAL_ROBOT_H__
#define __MANUAL_ROBOT_H__

#include "common.h"
#include "robot/robotBase.h"
#include "robot/commandExecutor.h"

class ManualRobot
{
public:
    ManualRobot(RobotBase& base, CommandExecutor& commandExecutor);

public:
    /*
     * Updates the manual Robot with the given input (use setInput)
     * @param delta is the delta Time in ms
     */
    void update(int delta);

    /*
     * Set the input / which axis will be moved how
     * @param input the input as a robot command
     */
    void setInput(RobCommand input);

private:

private:
    RobotBase& m_base;
    CommandExecutor& m_executor;

};

#endif
