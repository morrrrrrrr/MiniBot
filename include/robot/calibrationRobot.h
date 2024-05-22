
#ifndef __CALIBRATION_ROBOT_H__
#define __CALIBRATION_ROBOT_H__

#include "robot/robotBase.h"

class CalibrationRobot
{
public:
    CalibrationRobot(RobotBase& base);

public:
    void update(int delta);

private:
    RobotBase& m_base;

};

#endif
