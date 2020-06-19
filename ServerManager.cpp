#include "ServerManager.h"

ServerManager::ServerManager(int port, Roomba *roomba)
    : server(port)
{
    this->roomba = roomba;

    server.on("/startsafe", [this]() {
        this->handleStartSafe();
    });
    server.on("/startfull", [this]() {
        this->handleStartFull();
    });
        server.on("/oistop", [this]() {
        this->handleOIStop();
    });
    server.on("/poweroff", [this]() {
        this->handlePowerOff();
    });
    server.on("/left", [this]() {
        this->handleLeft();
    });
    server.on("/right", [this]() {
        this->handleRight();
    });
    server.on("/forward", [this]() {
        this->handleForward();
    });
    server.on("/backward", [this]() {
        this->handleBackward();
    });
    server.on("/drive", [this]() {
        this->handleDrive();
    });
    server.on("/stop", [this]() {
        this->handleStop();
    });
    server.on("/song", [this]() {
        this->handleSong();
    });
}

void ServerManager::begin()
{
    server.begin();
}

void ServerManager::handleClient(){
    server.handleClient();
}

void ServerManager::handleOIStop()
{
    roomba->stop();
    Serial.println("Open Interface stopped");
    handleRoot();
}

void ServerManager::handleStartSafe()
{
    roomba->startSafe();
    roomba->setPowerLED(128, 255);
    Serial.println("Open Interface started in safe mode");
    handleRoot();
}

void ServerManager::handleStartFull()
{
    roomba->startFull();
    Serial.println("Open Interface started in full mode");
    handleRoot();
}

void ServerManager::handlePowerOff()
{
    roomba->powerOff();
    Serial.println("Turned off");
    handleRoot();
}

void ServerManager::handleLeft()
{
    roomba->driveLeft(server.arg("speed").toInt());
    Serial.println("Turning left");
    handleRoot();
}

void ServerManager::handleRight()
{
    roomba->driveRight(server.arg("speed").toInt());
    Serial.println("Turning right");
    handleRoot();
}

void ServerManager::handleForward()
{
    roomba->driveWheels(server.arg("speed").toInt(), server.arg("speed").toInt());
    Serial.println("Going forward");
    handleRoot();
}

void ServerManager::handleBackward()
{
    roomba->driveWheels(-server.arg("speed").toInt(), -server.arg("speed").toInt());
    Serial.println("Going backward");
    handleRoot();
}

void ServerManager::handleDrive()
{
    roomba->driveWheels(server.arg("speedLeft").toInt(), server.arg("speedRight").toInt());
    handleRoot();
}

void ServerManager::handleStop()
{
    roomba->driveStop();
    Serial.println("Stopped");
    handleRoot();
}

void ServerManager::handleSong()
{
    roomba->playSound(2);
    Serial.println("Playing song");
    handleRoot();
}

void ServerManager::handleRoot()
{
    server.send(200, "text/html", "Command executed");
}