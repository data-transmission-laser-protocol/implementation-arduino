#include "DtlpTransmitter.h"

void DtlpTransmitter::_sendHandshakeSignal() {
    digitalWrite(_transmittersPins[0], HIGH);
    delay(_handshakeSignalMilliseconds);
    digitalWrite(_transmittersPins[0], LOW);
}

void DtlpTransmitter::sendTextAsBinary(const String text) {
    const unsigned long textLength = text.length();

    byte* binaryData = _textToBin(text);    

    _sendHandshakeSignal();

     for (unsigned long i = 0; i < textLength; ++i) {
        byte b = binaryData[i];

        // Set the pins according to the bits of the current byte
        digitalWrite(_transmittersPins[0], (b & 0b10000000) >> 7);
        digitalWrite(_transmittersPins[1], (b & 0b01000000) >> 6);
        digitalWrite(_transmittersPins[2], (b & 0b00100000) >> 5);
        digitalWrite(_transmittersPins[3], (b & 0b00010000) >> 4);
        digitalWrite(_transmittersPins[4], (b & 0b00001000) >> 3);
        digitalWrite(_transmittersPins[5], (b & 0b00000100) >> 2);
        digitalWrite(_transmittersPins[6], (b & 0b00000010) >> 1);
        digitalWrite(_transmittersPins[7], (b & 0b00000001));

        // Delay to allow the receiving end to read the bits
        delay(_bitDurationMilliseconds + 1);
    }
    
    // Send void byte to close the connection
    for (uint8_t i = 0; i < 8; i++) {
       digitalWrite(_transmittersPins[i], LOW);
    }

    delete[] binaryData;
}

void DtlpTransmitter::initTransmitter(const DtlpTransmitterConfig dtlpTransmitterConfig) {
    for (uint8_t i = 0; i < 8; i++) {
        _transmittersPins[i] = dtlpTransmitterConfig.transmittersPins[i];
    }
    
    _bitDurationMilliseconds = dtlpTransmitterConfig.bitDurationMilliseconds;
}

void DtlpTransmitter::encryptAndSendTextAsBinary(const String text, const EncryptionAlgo algo, const String key) {
    sendTextAsBinary(_encryptor->encrypt(text, algo, key));
}

byte* DtlpTransmitter::_textToBin(const String& s) {
     // Allocate memory for the byte array
    byte* byteArray = new byte[s.length()];

    // Convert each character in the string to its ASCII value
    for (unsigned int i = 0; i < s.length(); ++i) {
        byteArray[i] = s.charAt(i);
    }

    // Return the byte array
    return byteArray;
}
