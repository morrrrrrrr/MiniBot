
#include <Arduino.h>
#include "robot/robot.h"
#include "server.h"

Robot robot;
AsyncWebServer server(SERVER_PORT);

void setup() 
{
    Serial.begin(9600);

    Servo::setup();

    startWifi();

    // set up the server
    startServer(server, robot);
}

void loop()
{
    
}
