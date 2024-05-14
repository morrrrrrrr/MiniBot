
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
 *   * Servos 4x        (hardwareServo.h)
 *   * inverseKinematic (inverseKinematic.h)
 */
class RobotBase
{
public:
    RobotBase();

public:
    /*
     * Attach the write pins of the 4 servos
     * @param pins an array with 4 elements: [ s0Pin, ..., s3Pin ]
     */
    void attach(const uint8_t pins[]);
    /*
     * Attach the read pins of the 4 servos
     * @param pins an array with 4 elements: [ s0Pin, ..., s3Pin ]
     */
    void attachRead(const uint8_t pins[]);

public:
    /*
     * Let the robot drive to a position
     * @param pos   the position the robot should drive to
     * @param speed with which speed the robot should drive to the position (mm/s) (0 is instant)
     */
    void setPosition(RobPosition pos, uint16_t speed);

    /*
     * Returns if one or more of the servos are currently moving
     */
    bool isMoving() const;

public:
    /*
     * Translates the absolute movement that needs to be done and calculates the time, in which this is done
     * @param currentPosition reference to the current position of the robot (pass in m_position)
     * @param nextPosition    reference to the position, the robot wants to move to
     * @param speed           the speed of the movement (mm/s)
     * 
     * @return the time, that the movement will take
     */
    uint16_t speedToTime(RobPosition& currentPosition, RobPosition& nextPosition, uint16_t speed);

public:
    /*
     * Returns the current / last set position of the robot.
     * During a move, this returns the end position of the move
     */
    RobPosition getCurrentPosition() const;

public:
    /*
     * Set the lengths for all of the axes, in mm
     */
    void setAxisLengths(float ax0, float ax1, float ax3);

private:
    Servo            m_servos[4];
    InverseKinematic m_inverseKinematic;
    RobPosition      m_position;

public:
    Mat4 m_servoOffsets;

    // what is the minimum error
    float m_angleLimit;

}; 

#endif
