
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
    Servo(int ledc_channel, float low = 1.5f, float high = 2.5f);

public:
    /*
     * Setup the use of servos by setting up the Timer
     */
    static void setup();

    /*
    * Attach the servo data to a certain pin
    * @param dataPin the pin the servo will attach to
    */
    void attachWrite(uint8_t dataPin);

    /*
     * Attach the servo potentiometer to a certain pin (analog input)
     * @param readPin the pin the poti will attach to
     */
    void attachRead(uint8_t readPin);

    /*
     * Attaches the dataPin as the servo pin
     * @param dataPin The data pin of the servo
     */
    void attach(uint8_t dataPin);

    /*
     * Attaches the dataPin as the servo pin and the readPin as an analog input for reading the servo poti
     * @param dataPin The data pin of the servo
     * @param readPin The poti of the servo
     */
    void attach(uint8_t dataPin, uint8_t readPin);

    /*
    * Returns weather or not the servo is attached to a pin or not
    */
    bool isAttached() const;

    /*
     * Returns weather or not a read pin is attached
     */
    bool isReadAttached() const;

    /*
     * Write an angle to the PWM
     * @param angle    in radians (0 - PI)
     * @param time     in ms (0 is instant)
     * @param blocking only for time != 0: wait for the servo to reach its endpoint?
     */
    void write(float angle, uint16_t time = 0, bool blocking = false);

    /*
     * Read the current Servo position - read must be attached
     * @return the current angle of the servo in radians
     */
    float read();

public:
    /*
     * Reads the servo value and sets the output to it's value
     * - Helps with initializing the servos
     * - Read needs to be enabled for this function to work
     */
    void prepare();

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
    void startFadeOperation(int targetDuty, uint16_t speed, bool blocking);

private:
    /*
     * This gets called in the ISR when a fade operation ends
     */
    static void isr_handler(void* servo_ptr);

private:
    ledc_channel_t m_ledcChannel;

    struct
    {
        uint8_t write;
        uint8_t read;
    } m_gpioPins;

    float m_thresholdLow =  1.5f;
    float m_thresholdHigh = 2.5f;

    int m_dcLow, m_dcHigh;

    bool m_isMoving =        false;
    bool m_isWriteAttached = false;
    bool m_isReadAttached =  false;

    int m_currentDutyCycle;

    ledc_isr_handle_t m_intrHandle;

};

#endif
