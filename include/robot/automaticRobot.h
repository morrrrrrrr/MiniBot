
#ifndef __AUTOMATIC_ROBOT_H__
#define __AUTOMATIC_ROBOT_H__

#include "common.h"
#include "queue.h"
#include "robot/commandExecutor.h"
#include "robot/robotCommand.h"
#include "robot/robotBase.h"
#include "robot/program.h"

class AutomaticRobot
{
public:
    AutomaticRobot(RobotBase& base, CommandExecutor& commandExecutor);

public:
    /*
     * Updates with the current command, if done, checks, if it needs to fetch another one
     * @param delta the delta time in ms
     */
    void update(int delta);

    void start()
    {
        m_running = true;
    }
    void pause()
    {
        m_running = false;
    }
    void stop()
    {
        m_running = false;
        m_program.reset();
    }
    void step()
    {
        checkForNewCommand();
    }

private:
    /*
     * Checks, if the current command can be updated
     */
    void checkForNewCommand();

public:
    Program& getProgram()
    {
        return m_program;
    }

private:
    Program m_program;

    bool m_running;

private:
    RobotBase& m_base;
    CommandExecutor& m_executor;
    
};

#endif
