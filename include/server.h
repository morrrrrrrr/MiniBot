
#ifndef __SERVER_H__
#define __SERVER_H__

#define SERVER_PORT 80

#define WIFI_SSID     "HTLW3R-WEST"
#define WIFI_PASSWORD "HTLW3R-WEST"

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "AsyncJson.h"
#include "ArduinoJson.h"

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
    server.on("/api/mode/set", HTTP_GET, [&robot](AsyncWebServerRequest* request)
    {
        if (request->hasParam("mode"))
        {
            String value = request->getParam("mode")->value();
            
            robot.async_setMode(static_cast<RobotMode>(value.toInt()));
        }
        request->send(200);
    });
    server.on("/api/mode/get", HTTP_GET, [&robot](AsyncWebServerRequest* request)
    {
        request->send(200, "text/plain", String(robot.async_getMode()));
    });

    
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
    Serial.print("http://"); Serial.print(WiFi.localIP());  Serial.print(":"); Serial.println(SERVER_PORT);
}

#endif
