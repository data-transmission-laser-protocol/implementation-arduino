#include "DtlpTransmitter.h"

#define TRANSMITTER_LASER_PIN 8
#define BUTTON_PIN 9

DtlpTransmitter dtlpTransmitter;
DtlpTransmitterConfig config;

unsigned int textLength;

void setup() {
  pinMode(TRANSMITTER_LASER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  config.transmitterLaserPin = TRANSMITTER_LASER_PIN;
  config.bitDurationMilliseconds = 30;
  dtlpTransmitter.initTransmitter(config);

  Serial.begin(115200);
}

void loop() {
  // Transmit data from serial port
  if (Serial.available() > 0) {
    String text = Serial.readString();
    textLength = text.length();
    Serial.print("Sending (" + String(textLength) + " len): ");
    Serial.println(text);

    dtlpTransmitter.sendTextAsBinary(text);
  }

  // Transmit static data by clicking on a button
  if (digitalRead(BUTTON_PIN) == 0) {
    String text = "Button clicked!";
    textLength = text.length();
    Serial.print("Sending (" + String(textLength) + " len): ");
    Serial.println(text);

    dtlpTransmitter.sendTextAsBinary(text);
  } else {
    digitalWrite(TRANSMITTER_LASER_PIN, LOW);
  }
}
