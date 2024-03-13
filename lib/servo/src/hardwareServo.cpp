#include "hardwareServo.h"

#include "common.h"
#include <driver/ledc.h>



#define SERVO_FREQUENCY (1 / SERVO_PERIOD_TIME * 1000) 
#define SERVO_DUTY_CYCLE_MAX (powf(2, SERVO_FREQUENCY) - 1)



int mapftoi(float value, float fromLow, float fromHigh, int toLow, int toHigh)
{
    return ((value - fromLow) / fromHigh) * (toHigh - toLow) + toLow;
}


void Servo::isr_handler(void* servo_ptr)
{
    // Error-Handling: Check, if the argument is a nullptr
    if (!servo_ptr) return;

    // Re-interpret-cast the void* to a Servo* to access the servo
    Servo* servo = reinterpret_cast<Servo*>(servo_ptr);

    // set the moving flag of the servo to false
    servo->m_isMoving = false;

    return;
}


void Servo::setup()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode =      SERVO_SPEED_MODE,
        .duty_resolution = SERVO_DUTY_RESOLUTION,
        .timer_num  =      SERVO_TIMER,
        .freq_hz =         SERVO_FREQUENCY,
        .clk_cfg =         LEDC_AUTO_CLK
    };

    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ESP_ERROR_CHECK(ledc_fade_func_install(0));
}

Servo::Servo(ledc_channel_t ledc_channel, float low, float high) : 
    m_ledc_channel(ledc_channel),
    m_thresholdLow(low),
    m_thresholdHigh(high),
    m_dcLow ((m_thresholdLow   / SERVO_PERIOD_TIME) * SERVO_DUTY_CYCLE_MAX),
    m_dcHigh((m_thresholdHigh  / SERVO_PERIOD_TIME) * SERVO_DUTY_CYCLE_MAX),
    m_isAttached(false), m_isMoving(false),
    m_attachedPin(0),
    m_currentDutyCycle(0),
    m_intr_handle()
{ /* do nothing */}

void Servo::attach(uint8_t pin)
{
    // safe-guard to not attach twice
    if (isAttached()) return;

    // save the pin you attach to
    m_attachedPin = pin;

    // set the attached-flag to true
    m_isAttached = true;

    // call the ledc api to attach the pwm channel to the specified pin
    // ledcAttachPin(pin, m_PWMChannel);

    ledc_channel_config_t ledc_channel = {
        .gpio_num =   m_attachedPin,
        .speed_mode = SERVO_SPEED_MODE,
        .channel =    m_ledc_channel,
        .intr_type =  LEDC_INTR_FADE_END,
        .timer_sel =  SERVO_TIMER,
        .duty =       0,
        .hpoint =     0,
        .flags = {
            .output_invert = 0
        }
    };

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    ESP_ERROR_CHECK(ledc_isr_register(isr_handler, this, ESP_INTR_FLAG_LEVEL3, &m_intr_handle));
}

bool Servo::isAttached() const
{
    // check, if the pin is still the default value or not
    return m_isAttached;
}

void Servo::write(float angle, uint32_t time, bool block)
{
    /* NOTE: angle is given in radians */

    // Error-Handling: if the servo is moving, while the angle is changed, the angle cannot be changed.
    if (m_isMoving)
    {
        return;
    }

    // map the angle to the dutycycle
    int dc = mapftoi(angle, 0.0f, M_PI, m_dcLow, m_dcHigh);

    if (time)
    {
        // start a fade operation to the duty cycle using the time
        startFadeOperation(time, block, block);
    }
    else
    {
        // write the duty cycle to the pwm channel
        writeDutyCycle(dc);
    }
}

void Servo::writeDutyCycle(int targetDuty)
{
    m_currentDutyCycle = targetDuty;

    // ledcWrite(m_PWMChannel, targetDuty);

    ESP_ERROR_CHECK(ledc_set_duty(SERVO_SPEED_MODE, m_ledc_channel, targetDuty));
    ESP_ERROR_CHECK(ledc_update_duty(SERVO_SPEED_MODE, m_ledc_channel));
}

void Servo::startFadeOperation(int targetDuty, uint32_t time, bool block)
{
    m_isMoving = true;

    ledc_set_fade_time_and_start(
        SERVO_SPEED_MODE,
        m_ledc_channel,
        targetDuty,
        time,
        block ? LEDC_FADE_WAIT_DONE : LEDC_FADE_NO_WAIT
    );
}
