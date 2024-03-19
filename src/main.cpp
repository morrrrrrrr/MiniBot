
#include <Arduino.h>
#include "robot/robot.h"
#include "server.h"

Robot robot;
AsyncWebServer server(SERVER_PORT);

uint8_t pins[4] {
/* servo 0: */ 9,
/* servo 1: */ 10,
/* servo 2: */ 11,
/* servo 3: */ 12
};

void setup() 
{
    Serial.begin(9600);

    Servo::setup();

    robot.attach(pins);

    startWifi();
    startServer(server, robot);
}

void loop()
{
    robot.update();
}
