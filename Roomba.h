#ifndef ROOMBA_H
#define ROOMBA_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define clamp(value, min, max) (value < min ? min : value > max ? max : value)

class Roomba
{

private:
    // General
    byte ddPin;
    byte rxPin;
    byte txPin;
    SoftwareSerial softwareSerial;

    // LED
    bool debrisLED;
    bool spotLED;
    bool dockLED;
    bool warningLED;
    byte color;
    byte intensity;
    void updateLEDs();

public:
    // Constructor
    Roomba(byte ddPin, byte rxPin, byte txPin);

    // General
    void reset();
    void startSafe();
    void startFull();
    void stop();
    void powerOff();
    void seekDock();
    void playSound(int num);

    // LED
    void setPowerLED(byte color, byte intensity);
    void setDebrisLED(bool enable);
    void setSpotLED(bool enable);
    void setDockLED(bool enable);
    void setWarningLED(bool enable);

    // Motor
    void drive(int velocity, int radius);
    void driveWheels(int right, int left);
    void driveWheelsPWM(int rightPWM, int leftPWM);
    void driveStop(void);
    void driveLeft(int left);
    void driveRight(int right);
};

#endif