#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include "Roomba.h"
#include <Arduino.h>
#include <ESP32WebServer.h>

class ServerManager
{
private:
    ESP32WebServer server;
    Roomba *roomba;

    void handleStartSafe();
    void handleStartFull();
    void handleOIStop();
    void handlePowerOff();
    void handleDrive();
    void handleStop();
    void handleSong();
    void handleRoot();

public:
    // Constructor
    ServerManager(int port, Roomba *roomba);

    void begin();
    void handleClient();
};

#endif