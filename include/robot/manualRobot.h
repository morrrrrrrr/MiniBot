
#ifndef __MANUAL_ROBOT_H__
#define __MANUAL_ROBOT_H__

#include "common.h"
#include "robot/robotBase.h"

class ManualRobot
{
public:
    ManualRobot(RobotBase& base);

public:
    /*
     * Updates the manual Robot with the given input (use setInput)
     * @param delta is the delta Time in ms
     */
    void update(int delta);

    /*
     * Set the input / which axis will be moved how
     * from 0 to 1
     * @param input the input vector (4 dim)
     */
    void setInput(RobPosition input);

    /*
     * Set the manual speed - what speed is used when input is 1.0f
     * @param speed the speed in mm/s
     */
    void setSpeed(uint16_t speed);

private:
    RobPosition m_input;
    uint16_t    m_speed;

private:
    RobotBase& m_base;

};

#endif
