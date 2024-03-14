
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "robot/robotBase.h"

#include "robot/cmdRobot.h"

class Robot
{
public:
    Robot();

private:
    RobotBase m_base;

private:
    CommandControlledRobot m_ccRobot;

};

#endif
