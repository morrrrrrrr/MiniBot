
#ifndef __ROBOT_INTERFACE_H__
#define __ROBOT_INTERFACE_H__

#include "robot/robot.h"
#include "stringTools.h"

extern Robot robot;

namespace parse
{

    namespace command
    {

        bool parseMoveType(string& str, RobCommand& cmd)
        {
            if (str.length < 2)
            {
                return false;
            }

            char moveType = *str.data;
            // skip type and ';'
            str.move(2);

            switch (moveType)
            {
            case 'L':
                cmd.moveType = MoveType::Linear;
                break;
            case 'J':
                cmd.moveType = MoveType::Optimal;
                break;

            default:
                // error
                return false;
            }

            return true;
        }

        bool parseInt(string& str, uint16_t& num, char delim = ';')
        {
            string split;
            split.data = str.data;
            split.length = tools::strFind(str, delim);

            str.move(split.length + 1);

            num = atol(split.data);

            return true;
        }
        bool parseFloat(string& str, float& num, char delim = ';')
        {
            string split;
            split.data = str.data;
            split.length = tools::strFind(str, delim);

            str.move(split.length + 1);

            num = atof(split.data);

            return true;
        }

    } // namespace command

    bool parseCommand(string str, RobCommand& cmd)
    {
        if (!command::parseMoveType(str, cmd))             return false;
        if (!command::parseInt(str, cmd.speed))            return false;
        if (!command::parseFloat(str, cmd.target.point.x)) return false;
        if (!command::parseFloat(str, cmd.target.point.y)) return false;
        if (!command::parseFloat(str, cmd.target.point.z)) return false;
        if (!command::parseFloat(str, cmd.target.angle))   return false;

        return true;
    }

    bool parseProgram(string str, Program& prog)
    {
        uint16_t size;

        if (!command::parseInt(str, size, '|')) return false;

        prog.resize(size);

        for (uint16_t i = 0; i < size; i++)
        {
            RobCommand cmd;
            parseCommand(str, cmd);
            str.move(tools::strFind(str, '|'));
        }

        return true;
    }

} // namespace parse


namespace interface
{
    
    void changeRobotMode(string msg)
    {
        if (msg.length < 1)
        {
            // error
            return;
        }

        char mode = *msg.data;
        
        switch (mode)
        {
        case 'A':
            robot.changeMode(RobotMode::AUTOMATIC);
            break;
        case 'M':
            robot.changeMode(RobotMode::MANUAL);
            break;
        case 'O':
            robot.changeMode(RobotMode::OFF);
            break;

        default:
            break;
        }
    }

    void receiveProgram(string msg)
    {
        Program& program = robot.getAutomatic().getProgram();

        parse::parseProgram(msg, program);
    }

    void controlProgramFlow(string msg)
    {
        if (msg.length < 1)
        {
            // error
            return;
        }

        char mode = *msg.data;

        AutomaticRobot& automatic = robot.getAutomatic();

        switch (mode)
        {
        case 'S':
            automatic.start();
            break;
        case 'P':
            automatic.pause();
            break;
        case 'B':
            automatic.stop();
            break;

        default:
            break;
        }
    }

    void receiveCommand(string msg)
    {
        if (msg.length < 1)
        {
            // error
            return;
        }

        RobCommand cmd;

        if (!parse::parseCommand(msg, cmd))
        {
            return;
        }

        robot.getManual().setInput(cmd);
    }

} // namespace interface

/*
 * Connects the incoming serial messages to the robot's functions
 */
void onMessage(string msg)
{
    if (msg.length < 1)
    {
        // error
        return;
    }

    // extract the msg type (1st character)
    char type = *msg.data;
    msg.move(1);

    switch (type)
    {
    case 'M':
        interface::changeRobotMode(msg);
        break;

    case 'P':
        interface::receiveProgram(msg);
        break;

    case 'C':
        interface::controlProgramFlow(msg);
        break;

    case 'B':
        interface::receiveCommand(msg);
        break;

    default:
        break;
    }
}

#endif
