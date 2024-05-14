#include "hardwareServo.h"

#include "common.h"
#include <driver/ledc.h>



#define SERVO_FREQUENCY (1 / SERVO_PERIOD_TIME * 1000) 
#define SERVO_DUTY_CYCLE_MAX (powf(2, SERVO_DUTY_RESOLUTION) - 1)


template <typename Tx, typename Ty>
Ty myMap(Tx value, Tx fromLow, Tx fromHigh, Ty toLow, Ty toHigh)
{
    return ((value - fromLow) / fromHigh) * (toHigh - toLow) + toLow;
}

static IRAM_ATTR bool cb_ledc_fade_end_event(const ledc_cb_param_t *param, void *user_arg)
{
    // Error-Handling: Check, if the argument is a nullptr
    if (!user_arg) return false;

    // Re-interpret-cast the void* to a Servo* to access the servo
    Servo* servo = reinterpret_cast<Servo*>(user_arg);

    servo->resetIsMoving();

    return true;
}

void Servo::resetIsMoving()
{
    // set the moving flag of the servo to false
    m_isMoving = false;
}


void Servo::setup()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode =      SERVO_SPEED_MODE,
        .duty_resolution = SERVO_DUTY_RESOLUTION,
        .timer_num  =      SERVO_TIMER,
        .freq_hz =         50,
        .clk_cfg =         LEDC_AUTO_CLK
    };

    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ESP_ERROR_CHECK(ledc_fade_func_install(ESP_INTR_FLAG_SHARED));

    // ESP_ERROR_CHECK(ledc_isr_register(servo_isr_handler, (void*)this, ESP_INTR_FLAG_SHARED, &m_intrHandle));
    // ESP_ERROR_CHECK(ledc_isr_register(isr_handler, NULL, ESP_INTR_FLAG_SHARED, NULL));
}

Servo::Servo(int ledc_channel, float low, float high) : 
    m_ledcChannel(static_cast<ledc_channel_t>(ledc_channel)),
    m_thresholdLow(low),
    m_thresholdHigh(high),
    m_dcLow ((m_thresholdLow  / SERVO_PERIOD_TIME) * SERVO_DUTY_CYCLE_MAX),
    m_dcHigh((m_thresholdHigh / SERVO_PERIOD_TIME) * SERVO_DUTY_CYCLE_MAX),
    m_isWriteAttached(false), m_isMoving(false),
    m_gpioPins(),
    m_currentDutyCycle(0),
    m_intrHandle()
{ /* do nothing */}

void Servo::attachWrite(uint8_t pin)
{
    // safe-guard to not attach twice
    if (isAttached()) return;
    
    // save the pin you attach to
    m_gpioPins.write = pin;

    // set the attached-flag to true
    m_isWriteAttached = true;

    // call the ledc api to attach the pwm channel to the specified pin
    // ledcAttachPin(pin, m_PWMChannel);

    ledc_channel_config_t ledc_channel = {
        .gpio_num =   m_gpioPins.write,
        .speed_mode = SERVO_SPEED_MODE,
        .channel =    m_ledcChannel,
        .intr_type =  LEDC_INTR_FADE_END,
        .timer_sel =  SERVO_TIMER,
        .duty =       0,
        .hpoint =     0,
        .flags = {
            .output_invert = 0
        }
    };

    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    ledc_cbs_t callbacks = {
        .fade_cb = cb_ledc_fade_end_event
    };
    ESP_ERROR_CHECK(ledc_cb_register(SERVO_SPEED_MODE, m_ledcChannel, &callbacks, (void*)this));
}
void Servo::attachRead(uint8_t pin)
{
    // safe-guard to not attach twice
    if (isReadAttached()) return;

    m_gpioPins.read = pin;

    pinMode(pin, INPUT);
}

void Servo::attach(uint8_t dataPin)
{
    attachWrite(dataPin);
}
void Servo::attach(uint8_t dataPin, uint8_t readPin)
{
    attachWrite(dataPin);
    attachRead(readPin);
}

bool Servo::isAttached() const
{
    // check, if the pin is still the default value or not
    return m_isWriteAttached;
}
bool Servo::isReadAttached() const
{
    return m_isReadAttached;
}
bool Servo::isMoving() const
{
    return m_isMoving;
}

void Servo::write(float angle, uint16_t time, bool block)
{
    /* NOTE: angle is given in radians */

    // Error-Handling: if the servo is moving, while the angle is changed, the angle cannot be changed.
    if (m_isMoving)
    {
        return;
    }

    // Error-Handling: Servo is not attached
    if (!m_isWriteAttached)
    {
        return;
    }

    // map the angle to the dutycycle
    int dc = myMap<float, int>(angle, 0.0f, M_PI, m_dcLow, m_dcHigh);

    if (time)
    {
        // start a fade operation to the duty cycle using the time
        startFadeOperation(dc, time, block);
    }
    else
    {
        // write the duty cycle to the pwm channel
        writeDutyCycle(dc);
    }
}

float Servo::read()
{
    // return the servo angle in radians

    // check, if the read functionality is enabled:
    if (!isReadAttached()) return 0;

    // read value from the read pin (analog)
    uint16_t potiValue = analogRead(m_gpioPins.read);

    // convert the poti value to a float value
    return myMap<uint16_t, float>(potiValue, 0, 1023, 0.0f, M_PI);
}

void Servo::writeDutyCycle(int targetDuty)
{
    m_currentDutyCycle = targetDuty;

    // ledcWrite(m_PWMChannel, targetDuty);

    // Serial.println(targetDuty);

    ESP_ERROR_CHECK(ledc_set_duty(SERVO_SPEED_MODE, m_ledcChannel, targetDuty));
    ESP_ERROR_CHECK(ledc_update_duty(SERVO_SPEED_MODE, m_ledcChannel));
}

void Servo::startFadeOperation(int targetDuty, uint16_t time, bool block)
{
    m_isMoving = true;
    m_currentDutyCycle = targetDuty;

    ledc_set_fade_time_and_start(
        SERVO_SPEED_MODE,
        m_ledcChannel,
        targetDuty,
        time,
        block ? LEDC_FADE_WAIT_DONE : LEDC_FADE_NO_WAIT
    );

    if (block)
        resetIsMoving();
}

void Servo::prepare()
{
    write(read());
}
