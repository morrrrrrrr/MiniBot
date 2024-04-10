
#include <Arduino.h>
#include "robot/robot.h"
#include "serialInterface.h"

Robot robot;
// SerialCommands commands;
SerialInterface serialInterface;


uint8_t pins[4] {
/* servo 0: */ 9,
/* servo 1: */ 10,
/* servo 2: */ 11,
/* servo 3: */ 12
};

void onMessage(string msg)
{
    
}

void setup() 
{
    Serial.begin(9600);

    // Servo::setup();

    // commands.setCallback(onMessage);

    // robot.attach(pins);
}

void loop()
{
    // commands.update();
    serialInterface.update();
    // robot.update();
}
