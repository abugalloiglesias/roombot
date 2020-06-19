#include "Roomba.h"

Roomba::Roomba(byte ddPin, byte rxPin, byte txPin)
    : softwareSerial(rxPin, txPin)
{
  this->ddPin = ddPin;
  this->rxPin = rxPin;
  this->txPin = txPin;

  softwareSerial.begin(19200);
  pinMode(ddPin, OUTPUT);
}

void Roomba::reset()
{
  softwareSerial.write(7);
}

void Roomba::startSafe()
{
  softwareSerial.write(128);
  softwareSerial.write(131);
  delay(1000);
  setPowerLED(128, 255);
}

void Roomba::startFull()
{
  softwareSerial.write(128);
  softwareSerial.write(132);
  delay(1000);
  setPowerLED(255, 255);
}

void Roomba::stop()
{
  softwareSerial.write(173);
}

void Roomba::powerOff()
{
  softwareSerial.write(133);
}

void Roomba::seekDock()
{
  softwareSerial.write(143);
}

void Roomba::playSound(int num)
{
  switch (num)
  {
  case 1:
    softwareSerial.write("\x8c\x01\x04\x42\x20\x3e\x20\x42\x20\x3e\x20"); // [140] [1] [4] [68] [32] ... place "start sound" in slot 1
    softwareSerial.write("\x8d\x01");                                     // [141] [1] play it (in slot 1)
    break;

  case 2:
    softwareSerial.write("\x8c\x01\x06\x42\x10\x42\x10\x44\x20\x42\x20\x48\x20\x46\x20"); // [140] [1] [4] [68] [32] ... place "start sound" in slot 1
    softwareSerial.write("\x8d\x01");                                                     // [141] [1] play it (in slot 1)
    break;
  }
}

void Roomba::setPowerLED(byte color, byte intensity)
{
  this->color = color;
  this->intensity = intensity;
  softwareSerial.write(139);
  softwareSerial.write((byte)0x00);
  softwareSerial.write((byte)color);
  softwareSerial.write((byte)intensity);
}

void Roomba::setDebrisLED(bool enable)
{
  debrisLED = enable;
  updateLEDs();
}

void Roomba::setSpotLED(bool enable)
{
  spotLED = enable;
  updateLEDs();
}

void Roomba::setDockLED(bool enable)
{
  dockLED = enable;
  updateLEDs();
}

void Roomba::setWarningLED(bool enable)
{
  warningLED = enable;
  updateLEDs();
}

void Roomba::updateLEDs()
{
  softwareSerial.write(139);
  softwareSerial.write((debrisLED ? 1 : 0) + (spotLED ? 2 : 0) + (dockLED ? 4 : 0) + (warningLED ? 8 : 0));
  softwareSerial.write((byte)color);
  softwareSerial.write((byte)intensity);
}

void Roomba::drive(int velocity, int radius)
{
  clamp(velocity, -500, 500);
  clamp(radius, -2000, 2000);

  softwareSerial.write(137);
  softwareSerial.write(velocity >> 8);
  softwareSerial.write(velocity);
  softwareSerial.write(radius >> 8);
  softwareSerial.write(radius);
}

void Roomba::driveWheels(int right, int left)
{
  clamp(right, -500, 500);
  clamp(left, -500, 500);

  softwareSerial.write(145);
  softwareSerial.write(right >> 8);
  softwareSerial.write(right);
  softwareSerial.write(left >> 8);
  softwareSerial.write(left);
}

void Roomba::driveWheelsPWM(int rightPWM, int leftPWM)
{
  clamp(rightPWM, -255, 255);
  clamp(leftPWM, -255, 255);

  softwareSerial.write(146);
  softwareSerial.write(rightPWM >> 8);
  softwareSerial.write(rightPWM);
  softwareSerial.write(leftPWM >> 8);
  softwareSerial.write(leftPWM);
}

void Roomba::driveStop(void)
{
  drive(0, 0);
}

void Roomba::driveLeft(int left)
{
  driveWheels(left, 0);
}

void Roomba::driveRight(int right)
{
  driveWheels(0, right);
}
