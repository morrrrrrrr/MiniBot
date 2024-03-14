
#ifndef __ROBOT_BASE_H__
#define __ROBOT_BASE_H__

#include "hardwareServo.h"
#include "inverseKinematic.h"

/*
 * The RobotBase-class is a container for an API, that handles
 * the communication between the Robot and the Servos
 * 
 * For the hardwareServos, this uses LEDC Channels 0 to 3
 * 
 * Contains:
 *   * Servos             4x  (hardwareServo.h)
 *   * inverseKinematic       (inverseKinematic.h)
 */
class RobotBase
{
public:
    RobotBase();

public:
    /*
     * Let the robot drive to a position
     * @param pos   the position the robot should drive to
     * @param speed with which speed the robot should drive to the position (0 is instant)
     */
    void setPosition(const RobPosition& pos, uint16_t speed);

    /*
     * Returns if one or more of the servos are currently moving
     */
    bool isMoving();

private:
    Servo            m_servos[4];
    InverseKinematic m_inverseKinematic;
    RobPosition      m_position;

}; 

#endif
