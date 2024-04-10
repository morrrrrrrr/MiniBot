
#ifndef __COMMAND_EXECUTOR_H__
#define __COMMAND_EXECUTOR_H__

#include "common.h"
#include "robot/robotBase.h"
#include "robot/robotCommand.h"
#include "robError.h"

class CommandExecutor
{
public:
    CommandExecutor(RobotBase& robotBase);

public:
    void update(int delta);

    void setCommand(const RobCommand& cmd);
    bool isCommandActive();

private:
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
    void startCommand(const RobCommand& command);

private:
    RobCommand m_currentCommand;
    uint16_t m_commandProgress;

    // flag weather or not a current command is set
    bool m_commandActive;

    bool m_running = false;

    RobPosition m_linearStart;

private:
    RobotBase& m_base;

};

#endif
