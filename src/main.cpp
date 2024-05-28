
#include <Arduino.h>
#include "robot/robot.h"
#include "serialInterface.h"
#include "robotInterface.h"

Robot robot(Mat4(50, 50, 50, 50));
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

    Servo::setup();

    serialInterface.setCallback(onMessage);
    
    robot.attach(pins);
}

bool lastCommandActive = false;

void loop()
{
    serialInterface.update();
    robot.update();

    if (!robot.getExecutor().isCommandActive() && lastCommandActive)
    {
        // current command stopped -> sending a message
        Serial.println("C");
    }

    lastCommandActive = robot.getExecutor().isCommandActive();

    if (check_robot_error())
    {
        Serial.print("ERROR: code "); Serial.println(robError);

        Serial.read();

        robError = rob_error_t::NO_ERROR;
    }

    delay(100);
}
