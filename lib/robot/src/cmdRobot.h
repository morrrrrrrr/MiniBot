
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "common.h"
#include "queue.h"
#include "robCommand.h"
#include "inverseKinematic.h"

class CommandControlledRobot
{
public:
    CommandControlledRobot(RobPosition& robPositionRef);

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
     */
    void updateCurrentCommand();

private:
    Queue<RobCommand, 10> m_commandQueue;

    RobCommand m_currentCommand;
    float m_commandProgress; // 0 to 1

    // flag weather or not a current command is set
    bool m_commandActive;

private:
    RobPosition& m_currentPosition;
    
};

#endif
