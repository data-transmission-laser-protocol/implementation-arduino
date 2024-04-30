
#include "DtlpTransmitter.h"

void DtlpTransmitter::_sendHandshakeSignal() {
    digitalWrite(_transmitterLaserPin, HIGH);
    delay(_handshakeSignalMilliseconds);
    digitalWrite(_transmitterLaserPin, LOW);
}

void DtlpTransmitter::sendTextAsBinary(const String text) {
    const unsigned int textLength = text.length();

    _sendHandshakeSignal();

    for (unsigned int i = 0; i < textLength; i++) {
        char c = text.charAt(i);
        byte b = c;

        for (int j = 7; j >= 0; j--) {
            bool bitVal = bitRead(b, j);
            if (bitVal) {
                digitalWrite(_transmitterLaserPin, HIGH);  // Turn on the laser
            } else {
                digitalWrite(_transmitterLaserPin, LOW);  // Turn off the laser
            }

            if (i != textLength) {
                delay(_bitDurationMilliseconds);  // Delay between bits
            }

        }
    }
    digitalWrite(_transmitterLaserPin, LOW);
}

void DtlpTransmitter::initTransmitter(const DtlpTransmitterConfig dtlpTransmitterConfig) {
    _transmitterLaserPin = dtlpTransmitterConfig.transmitterLaserPin;
    _bitDurationMilliseconds = dtlpTransmitterConfig.bitDurationMilliseconds;
}

void DtlpTransmitter::encryptAndSendTextAsBinary(const String text, const EncryptionAlgo algo, const String key) {
    sendTextAsBinary(_encryptor->encrypt(text, algo, key));
}