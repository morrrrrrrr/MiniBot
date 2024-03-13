
#ifndef __HARDWARE_SERVO_H__
#define __HARDWARE_SERVO_H__

#include "common.h"

class Servo
{
public:
  /*
   * Constructor for the Servo-Object
   * @param PWMChannel    which PWM channel of the LEDC-Api will this servo use
   * @param PWMResolution what is the PWM Resolution (max 20) (def 10)
   * @param PWMtime       the T of the PWM in ms -> (def 20ms)
   */
  Servo(uint8_t PWMChannel, uint8_t PWMResolution = 10, uint8_t PWMtime = 20);

public:
  /*
   * Attach the servo to a certain pin
   * @param pin the pin the servo will attach to
   */
  void attach(uint8_t pin);

  /*
   * Returns weather or not the servo is attached to a pin or not
   */
  bool isAttached();

  /*
   * Write an angle to the PWM
   * @param angle in radians (0 - PI)
   */
  void write(float angle);

private:
  /*
   * Write a duty cycle to the attached pin
   * @param dutyCycle the duty cycle (0 to (2**PWMResolution - 1))
   */
  void writeDutyCycle(int dutyCycle);

private:
  uint8_t m_PWMChannel;
  uint8_t m_PWMResolution;
  uint8_t m_PWMTime;

  uint8_t m_attachedPin;

  // this is 2**PWMResolution - 1, calculated only once
  int m_dutyCycleMax;

  const float m_thresholdLow =  1.5f;
  const float m_thresholdHigh = 2.5f;

  int m_dcLow, m_dcHigh;

};

#endif
