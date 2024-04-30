#include "DtlpReceiver.h"

#define RECEIVER_PIN 8
#define LED_PIN 9

DtlpReceiver dtlpReceiver;
DtlpReceiverConfig config;

// Define your secret key for decryption
const String key = "TYPE_YOUR_KEY_HERE";

uint8_t lastStatus = ConnectionStatus::INACTIVE_CONNECTION;

void turnOnLed() {
  digitalWrite(LED_PIN, HIGH);
}

void turnOffLed() {
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  pinMode(RECEIVER_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  config.bitDurationMilliseconds = 30;
  dtlpReceiver.initReceiver(config);

  Serial.begin(115200);
  turnOffLed();
}

void loop() {
  const uint8_t signalValue = digitalRead(RECEIVER_PIN) == LOW ? 1 : 0;

  const uint8_t status = dtlpReceiver.status();
  dtlpReceiver.handleProcessorInterator(signalValue);

  if (lastStatus != status) {
    lastStatus = status;

    if (lastStatus == ConnectionStatus::INACTIVE_CONNECTION) {
      Serial.println("Received: " + dtlpReceiver.decryptAndGetReceivedData(EncryptionAlgo::XOR, key));
      Serial.println("Connection Deactivated");
      turnOffLed();
    } else if (lastStatus == ConnectionStatus::PROCESSING_HANDSHAKE_SIGNAL) {
      Serial.println("Processing Handshake Signal");
    } else {
      Serial.println("Processing Incoming Data...");
      turnOnLed();
    }
  }
}
