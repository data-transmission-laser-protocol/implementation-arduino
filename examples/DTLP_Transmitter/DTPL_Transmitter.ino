#include <Base64.h>

#include "DtlpTransmitter.h"
#include "EncryptionAlgo.h"

#define TRANSMITTER_LASER_PIN 8
#define BUTTON_PIN 9

DtlpTransmitter dtlpTransmitter;
DtlpTransmitterConfig config;

// Define your secret key for encryption
const String key = "TYPE_YOUR_KEY_HERE";

void setup() {
  Serial.begin(115200);
  pinMode(TRANSMITTER_LASER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  config.transmitterLaserPin = TRANSMITTER_LASER_PIN;
  config.bitDurationMilliseconds = 30;
  dtlpTransmitter.initTransmitter(config);
}

void loop() {
  if (Serial.available() > 0) {
    String text = Serial.readString();
    Serial.print("Sending (" + String(text.length()) + " len): ");
    Serial.println(text);

    dtlpTransmitter.encryptAndSendTextAsBinary(text, EncryptionAlgo::XOR, key);
  }

  if (digitalRead(BUTTON_PIN) == 0) {
    String text = "Button clicked!";
    Serial.print("Sending (" + String(text.length()) + " len): ");
    Serial.println(text);

    dtlpTransmitter.encryptAndSendTextAsBinary(text, EncryptionAlgo::XOR, key);
  } else {
    digitalWrite(TRANSMITTER_LASER_PIN, LOW);
  }
}
