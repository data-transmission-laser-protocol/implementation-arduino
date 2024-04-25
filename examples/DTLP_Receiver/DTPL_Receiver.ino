#include "DtlpReceiver.h"

#define RECEIVER_PIN 8
#define LED_PIN 9

DtlpReceiver dtlpReceiver;
DtlpReceiverConfig config;

uint8_t lastStatus = dtlpReceiver.INACTIVE_CONNECTION;

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

    if (lastStatus == dtlpReceiver.INACTIVE_CONNECTION) {
      Serial.println("Received: " + dtlpReceiver.getReceivedData());
      Serial.println("Connection Deactivated");
      turnOffLed();
    } else if (lastStatus == dtlpReceiver.PROCESSING_HANDSHAKE_SIGNAL) {
      Serial.println("Processing Handshake Signal");
    } else {
      Serial.println("Processing Incoming Data...");
      turnOnLed();
    }
  }
}
