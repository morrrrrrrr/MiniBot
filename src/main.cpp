
#include <Arduino.h>
#include "robot/robot.h"
#include "serialCommand.h"

Robot robot;
SerialCommands commands;

uint8_t pins[4] {
/* servo 0: */ 9,
/* servo 1: */ 10,
/* servo 2: */ 11,
/* servo 3: */ 12
};

void onMessage(serial::Message& message)
{
    switch (message.header.type)
    {
    default:
        serial::Message msg(0, 0);
        commands.writeMessage(msg);
        break;
    }
}

void setup() 
{
    Serial.begin(9600);

    // Servo::setup();

    commands.setCallback(onMessage);

    // robot.attach(pins);
}

void loop()
{
    commands.update();
    // robot.update();
}
