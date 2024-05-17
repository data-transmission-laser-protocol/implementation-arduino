#include "DtlpReceiver.h"

#define RECEIVER_0_PIN 2
#define RECEIVER_1_PIN 3
#define RECEIVER_2_PIN 4
#define RECEIVER_3_PIN 5
#define RECEIVER_4_PIN 6
#define RECEIVER_5_PIN 7
#define RECEIVER_6_PIN 9
#define RECEIVER_7_PIN 10
#define LED_PIN 11

DtlpReceiver dtlpReceiver;
DtlpReceiverConfig config;

// Define your secret key for decryption
// Use this only if you need to decrypt incoming data
const String key = "TYPE_YOUR_KEY_HERE";

uint8_t lastStatus = ConnectionStatus::INACTIVE_CONNECTION;

void turnOnLed() {
  digitalWrite(LED_PIN, HIGH);
}

void turnOffLed() {
  digitalWrite(LED_PIN, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(RECEIVER_0_PIN, INPUT_PULLUP);
  pinMode(RECEIVER_1_PIN, INPUT_PULLUP);
  pinMode(RECEIVER_2_PIN, INPUT_PULLUP);
  pinMode(RECEIVER_3_PIN, INPUT_PULLUP);
  pinMode(RECEIVER_4_PIN, INPUT_PULLUP);
  pinMode(RECEIVER_5_PIN, INPUT_PULLUP);
  pinMode(RECEIVER_6_PIN, INPUT_PULLUP);
  pinMode(RECEIVER_7_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  config.receiversPins[0] = RECEIVER_0_PIN;
  config.receiversPins[1] = RECEIVER_1_PIN;
  config.receiversPins[2] = RECEIVER_2_PIN;
  config.receiversPins[3] = RECEIVER_3_PIN;
  config.receiversPins[4] = RECEIVER_4_PIN;
  config.receiversPins[5] = RECEIVER_5_PIN;
  config.receiversPins[6] = RECEIVER_6_PIN;
  config.receiversPins[7] = RECEIVER_7_PIN;
  config.bitDurationMilliseconds = 30;
  dtlpReceiver.initReceiver(config);

  turnOffLed();
}

void loop() {
  const bool byte[8] = {
    digitalRead(RECEIVER_0_PIN),
    digitalRead(RECEIVER_1_PIN),
    digitalRead(RECEIVER_2_PIN),
    digitalRead(RECEIVER_3_PIN),
    digitalRead(RECEIVER_4_PIN),
    digitalRead(RECEIVER_5_PIN),
    digitalRead(RECEIVER_6_PIN),
    digitalRead(RECEIVER_7_PIN)
  };

  dtlpReceiver.handleProcessorInterator(byte);
  const uint8_t status = dtlpReceiver.status();
  
  if (lastStatus != status) {
    lastStatus = status;
    
    if (lastStatus == ConnectionStatus::INACTIVE_CONNECTION) {
      // Serial.println("Received: " + dtlpReceiver.decryptAndGetReceivedData(EncryptionAlgo::XOR, key));
      Serial.println("Received: " + dtlpReceiver.getReceivedData());
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
