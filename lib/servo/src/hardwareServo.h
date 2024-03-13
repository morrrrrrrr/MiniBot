
#ifndef __HARDWARE_SERVO_H__
#define __HARDWARE_SERVO_H__

#include "common.h"

#include <driver/ledc.h>

#define SERVO_TIMER                 LEDC_TIMER_0
#define SERVO_DUTY_RESOLUTION       LEDC_TIMER_10_BIT
#define SERVO_PERIOD_TIME           20 // in ms
#define SERVO_SPEED_MODE            LEDC_LOW_SPEED_MODE

class Servo
{
public:
    /*
    * Constructor for the Servo-Object
    * @param ledc_channel which PWM channel of the LEDC-Api will this servo use
    * @param low          T on of the PWM when the servo is left most (ms)
    * @param high         T on of the PWM when the servo is right most (ms)
    */
    Servo(ledc_channel_t ledc_channel, float low = 1.5f, float high = 2.5f);

public:
    /*
     * Setup the use of servos by setting up the Timer
     */
    static void setup();

    /*
    * Attach the servo to a certain pin
    * @param pin the pin the servo will attach to
    */
    void attach(uint8_t pin);

    /*
    * Returns weather or not the servo is attached to a pin or not
    */
    bool isAttached() const;

    /*
    * Write an angle to the PWM
    * @param angle    in radians (0 - PI)
    * @param time     in ms (0 is instant)
    * @param blocking only for time != 0: wait for the servo to reach its endpoint?
    */
    void write(float angle, uint32_t speed = 0, bool blocking = false);

private:
    /*
    * Write a duty cycle to the attached pin
    * @param dutyCycle the duty cycle (0 to (2**PWMResolution - 1))
    */
    void writeDutyCycle(int targetDuty);

    /*
     * Start a Fade operation (= slow movement)
     * Fade starts from the current duty cycle
     * @param dutyCycle to which duty cycle will the fade be
     * @param speed     the speed of the fade
     */
    void startFadeOperation(int targetDuty, uint32_t speed, bool blocking);

private:
    /*
     * This gets called in the ISR when a fade operation ends
     */
    static void isr_handler(void* servo_ptr);

private:
    ledc_channel_t m_ledc_channel;

    uint8_t m_attachedPin;

    float m_thresholdLow =  1.5f;
    float m_thresholdHigh = 2.5f;

    int m_dcLow, m_dcHigh;

    bool m_isMoving = false;
    bool m_isAttached = false;

    int m_currentDutyCycle;

    ledc_isr_handle_t m_intr_handle;

};

#endif
