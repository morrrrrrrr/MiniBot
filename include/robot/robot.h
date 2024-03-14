
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "robot/robotBase.h"

#include "robot/automaticRobot.h"

class Robot
{
public:
    Robot();

private:
    RobotBase m_base;

private:
    AutomaticRobot m_ccRobot;

};

#endif
