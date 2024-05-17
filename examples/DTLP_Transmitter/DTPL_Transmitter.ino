#include <Base64.h>

#include "DtlpTransmitter.h"
#include "EncryptionAlgo.h"

#define TRANSMITTER_LASER_0_PIN 2
#define TRANSMITTER_LASER_1_PIN 3
#define TRANSMITTER_LASER_2_PIN 4
#define TRANSMITTER_LASER_3_PIN 5
#define TRANSMITTER_LASER_4_PIN 6
#define TRANSMITTER_LASER_5_PIN 7
#define TRANSMITTER_LASER_6_PIN 9
#define TRANSMITTER_LASER_7_PIN 10
#define BUTTON_PIN 11

DtlpTransmitter dtlpTransmitter;
DtlpTransmitterConfig config;

// Define your secret key for encryption
// Use this only if you need to encrypt the data before sending
const String key = "TYPE_YOUR_KEY_HERE";

void setup() {
  Serial.begin(115200);
  
  pinMode(TRANSMITTER_LASER_0_PIN, OUTPUT);
  pinMode(TRANSMITTER_LASER_1_PIN, OUTPUT);
  pinMode(TRANSMITTER_LASER_2_PIN, OUTPUT);
  pinMode(TRANSMITTER_LASER_3_PIN, OUTPUT);
  pinMode(TRANSMITTER_LASER_4_PIN, OUTPUT);
  pinMode(TRANSMITTER_LASER_5_PIN, OUTPUT);
  pinMode(TRANSMITTER_LASER_6_PIN, OUTPUT);
  pinMode(TRANSMITTER_LASER_7_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  config.transmittersPins[0] = TRANSMITTER_LASER_0_PIN;
  config.transmittersPins[1] = TRANSMITTER_LASER_1_PIN;
  config.transmittersPins[2] = TRANSMITTER_LASER_2_PIN;
  config.transmittersPins[3] = TRANSMITTER_LASER_3_PIN;
  config.transmittersPins[4] = TRANSMITTER_LASER_4_PIN;
  config.transmittersPins[5] = TRANSMITTER_LASER_5_PIN;
  config.transmittersPins[6] = TRANSMITTER_LASER_6_PIN;
  config.transmittersPins[7] = TRANSMITTER_LASER_7_PIN;
  config.bitDurationMilliseconds = 30;
  dtlpTransmitter.initTransmitter(config);
}

void loop() {

  if (Serial.available() > 0) {
    String text = Serial.readString();
    Serial.print("Sending (" + String(text.length()) + " len): ");
    Serial.println(text);

    // dtlpTransmitter.encryptAndSendTextAsBinary(text, EncryptionAlgo::XOR, key);
    dtlpTransmitter.sendTextAsBinary(text);
  }

  if (digitalRead(BUTTON_PIN) == 0) {
    String text = "Button clicked!";
    Serial.print("Sending (" + String(text.length()) + " len): ");
    Serial.println(text);

    // dtlpTransmitter.encryptAndSendTextAsBinary(text, EncryptionAlgo::XOR, key);
    dtlpTransmitter.sendTextAsBinary(text);
  }
}
