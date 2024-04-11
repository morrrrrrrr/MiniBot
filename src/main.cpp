
#include <Arduino.h>
#include "robot/robot.h"
#include "serialInterface.h"
#include "robotInterface.h"

Robot           robot;
SerialInterface serialInterface;

uint8_t pins[4] {
/* servo 0: */ 9,
/* servo 1: */ 10,
/* servo 2: */ 11,
/* servo 3: */ 12
};

void setup() 
{
    Serial.begin(9600);

    // Servo::setup();

    serialInterface.setCallback(onMessage);
    // commands.setCallback(onMessage);

    // robot.attach(pins);
}

void loop()
{
    // commands.update();
    serialInterface.update();
    // robot.update();
}
