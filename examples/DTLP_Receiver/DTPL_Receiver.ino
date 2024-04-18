#define RECEIVER_PIN 8
#define LED_PIN 9

#include "DtlpReceiver.h"
DtlpReceiver dtlpReceiver;

unsigned int lastStatus = dtlpReceiver.INACTIVE_CONNECTION;

void turnOnLed() {
    digitalWrite(LED_PIN, HIGH);
}

void turnOffLed() {
    digitalWrite(LED_PIN, LOW);
}

void setup() {
    pinMode(RECEIVER_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);
    turnOffLed();
}

void loop() {
    const unsigned int signalValue = digitalRead(RECEIVER_PIN) == LOW;

    const unsigned int status = dtlpReceiver.status();
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
