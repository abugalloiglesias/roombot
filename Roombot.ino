#include "Roomba.h"
#include "ServerManager.h"
#include <ESP8266WiFi.h>

// WIFI
String ssid = "HACK_THE_MALL2";
String password = "hackthemall";

int ddPin = D1;
int rxPin = D5;
int txPin = D6;

Roomba roomba(ddPin, rxPin, txPin);
ServerManager serverManager(80, &roomba);

void setup()
{
  Serial.begin(19200);
  Serial.println("Roomba Remote Control");

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid.c_str(), password.c_str());

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start server
  Serial.println("Starting HTTP server...");
  serverManager.begin();
  Serial.println("Server started");
}

void loop()
{
  serverManager.handleClient();
}