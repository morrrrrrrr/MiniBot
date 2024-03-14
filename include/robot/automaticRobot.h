
#ifndef __AUTOMATIC_ROBOT_H__
#define __AUTOMATIC_ROBOT_H__

#include "common.h"
#include "queue.h"
#include "robot/robotCommand.h"
#include "robot/robotBase.h"

class AutomaticRobot
{
public:
    AutomaticRobot(RobotBase& base);

public:
    /*
     * Updates with the current command, if done, checks, if it needs to fetch another one
     * @param delta the delta time in ms
     */
    void update(int delta);

private:
    /*
     * Checks, if the current command can be updated
     */
    void checkForNewCommand();

    /*
     * Updates the current command. Check the
     * m_commandActive flag before calling
     * this function
     * @param delta the delta time in ms
     */
    void updateCurrentCommand(int delta);

private:
    /*
     * Handle Linear Movement
     * @param command the robot command - it is already checked to be a moveL
     * @param delta   the delta time in ms
     * @return true if the command is done
     */
    bool handleLinearMove(RobCommand& command, int delta);

    /*
     * Handle Optimal Movement
     * @param command the robot command - it is already checked to be a moveJ
     * @param delta   the delta time in ms
     * @return true if the command is done
     */
    bool handleOptimalMove(RobCommand& command, int delta);

private:
    /*
     * start the specified command to be executed
     */
    void startCommand(RobCommand command);

private:
    Queue<RobCommand, 10> m_commandQueue;

    RobCommand m_currentCommand;
    uint16_t m_commandProgress;

    // flag weather or not a current command is set
    bool m_commandActive;

    RobPosition m_linearStart;

private:
    RobotBase& m_base;
    
};

#endif
