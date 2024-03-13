#include "hardwareServo.h"

#include "common.h"

#define NULLPIN 255

Servo::Servo(uint8_t PWMChannel, uint8_t PWMResolution, uint8_t PWMTime) : 
  m_PWMChannel(PWMChannel), m_PWMResolution(PWMResolution), m_PWMTime(PWMTime), m_attachedPin(NULLPIN)
{
  const int PWMFrequency = 1 / PWMTime * 1000;

  ledcSetup(PWMChannel, PWMFrequency, PWMResolution);
  m_dutyCycleMax = pow(2, PWMFrequency) - 1;

  // calculate the low and high duty cycle points
  m_dcLow = (m_thresholdLow  / m_PWMTime) * m_dutyCycleMax;
  m_dcHigh = (m_thresholdLow  / m_PWMTime) * m_dutyCycleMax;
}

void Servo::attach(uint8_t pin)
{
  // safe-guard to not attach twice
  if (isAttached()) return;

  // save the pin you attach to
  m_attachedPin = pin;

  // call the ledc api to attach the pwm channel to the specified pin
  ledcAttachPin(pin, m_PWMChannel);
}

bool Servo::isAttached()
{
  // check, if the pin is still the default value or not
  return m_attachedPin != NULLPIN;
}

int mapf(float value, float fromLow, float fromHigh, int toLow, int toHigh)
{
  return ((value - fromLow) / fromHigh) * (toHigh - toLow) + toLow;
}

void Servo::write(float angle)
{
  /* NOTE: angle is given in radians */

  // map the angle to the dutycycle
  int dc = mapf(angle, 0.0f, M_PI, m_dcLow, m_dcHigh);

  // write the duty cycle to the pwm channel
  writeDutyCycle(dc);
}

void Servo::writeDutyCycle(int dutyCycle)
{
  ledcWrite(m_PWMChannel, dutyCycle);
}
