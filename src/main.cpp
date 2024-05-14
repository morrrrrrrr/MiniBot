
#include <Arduino.h>
#include "robot/robot.h"
#include "serialInterface.h"
#include "robotInterface.h"

Robot           robot(Mat4(50, 50, 50, 50));
SerialInterface serialInterface;

uint8_t pins[4] {
/* servo 0: */ 27,
/* servo 1: */ 26,
/* servo 2: */ 25,
/* servo 3: */ 33
};

void setup() 
{
    Serial.begin(9600);

    Serial.println("Hello, World!");

    Servo::setup();

    serialInterface.setCallback(onMessage);

    robot.attach(pins);
}

void loop()
{
    serialInterface.update();
    robot.update();
}
