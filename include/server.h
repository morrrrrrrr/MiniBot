
#ifndef __SERVER_H__
#define __SERVER_H__

#define SERVER_PORT 80

#define WIFI_SSID     "HTLW3R-WEST"
#define WIFI_PASSWORD "HTLW3R-WEST"

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "robot/robot.h"

void startWifi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi!\nESP's IP adress: " + WiFi.localIP());
}

void setupBackend(AsyncWebServer& server, Robot& robot)
{
    
}
void setupFrontend(AsyncWebServer& server, Robot& robot)
{
    
}

void startServer(AsyncWebServer& server, Robot& robot)
{
    setupBackend(server, robot);
    setupFrontend(server, robot);

    server.begin();
    Serial.println("Server started. IP:PORT:");
    Serial.println(WiFi.localIP() + ":" + SERVER_PORT);
}

#endif
