
# Hardware Servo - Library

Written by morrrrrrrrrrrr

Uses the [esp-ledcontrol](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/ledc.html)
library for controlling up to 8 servos with the esp

At default, this library uses the Timer 0. This can be changed in the [hardwareServo.h](src/hardwareServo.h) file

## Functionality

This libary is non-blocking, meaning, that the PWM signal is created at the hardware not the software

### Features

* Writing to Servos
* Servo Speed Control
* Attaching a wire to the Servos potentiometer for reading

## Usage

### Constructor

to create a Servo-Object, you can call the Constructor.

The Constructor takes one Argument:

* **ledc-Channel:**
    
    * integer
    * Check the enum `LEDC_CHANNEL_MAX` to see the maximum allowed channels / servos
    * You can also use the `LEDC_CHANNEL_0` to `LEDC_CHANNEL_7`

```cpp
Servo myServo1(LEDC_CHANNEL_0);
Servo myServo2(LEDC_CHANNEL_1);
```

### Setup

Before writing or reading from the Servo, you need to setup

`setup()` - is a static function in the servo class. Call this before attaching any servos

```cpp
void setup()
{
    Servo::setup();

    // attaching any servos
}
```

### Attaching

You can attach the Servo with:

After attaching the servo still isn't moving, only after writing a value to it, a data is sent

* Only the data pin:
    * You can write
    * You can speed-control

```cpp
void setup()
{
    Servo::setup();

    myServo.attach(9);
}
```

* With read and data pin:
    * You can write
    * You can speed-control
    * You can read

```cpp
void setup()
{
    Servo::setup();

    myServo.attach(9, A0);
}
```

### Writing without speed-control

Give the angle in **radians**

```cpp
myServo.write(M_PI / 2.0f);
```

### Writing with speed-control

* angle: in radians
* time:  in ms
* blocking: should the function wait until the servo is at position

```cpp
myServo.write(M_PI / 2.0f, 1000, false);
```

### Reading from the servo

```cpp
float angle_in_radians = myServo.read();
```

### Preparing

Sets the current value to the actual servo value:
When starting, this can be used to stop the servos from
instantly moving to an initial value

```cpp
myServo.prepare();
```

All this does in the background is:

```cpp
myServo.write(myServo.read());
```
