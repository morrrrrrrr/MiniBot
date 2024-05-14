
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "robot/robotBase.h"
#include "robot/commandExecutor.h"

#include "robot/automaticRobot.h"
#include "robot/manualRobot.h"

#include "common.h"
#include "deltaTime.h"

enum RobotMode : uint8_t
{
    OFF, AUTOMATIC, MANUAL
};

class Robot
{
public:
    Robot(const Mat4& axisLengths);

public:
    void attach(const uint8_t pins[]);
    void attachRead(const uint8_t pins[]);

    inline void setServoOffsets(float s0, float s1, float s2, float s3);
    
public:
    void update();

public:
    void changeMode(RobotMode mode);

public:
    AutomaticRobot& getAutomatic();
    ManualRobot& getManual();
    RobotBase& getBase();

private:
    RobotMode m_mode;
    Time      m_time;

private:
    RobotBase       m_base;
    CommandExecutor m_executor;

private:
    AutomaticRobot m_automatic;
    ManualRobot    m_manual;

};

#endif
