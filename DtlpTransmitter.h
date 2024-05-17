#include <Arduino.h>
#include "EncryptionAlgo.h"
#include "Encryptor.h"

#ifndef DTLP_TRANSMITTER_H
#define DTLP_TRANSMITTER_H

typedef struct {
    uint8_t bitDurationMilliseconds;
    uint8_t transmittersPins[8];
} DtlpTransmitterConfig;

class DtlpTransmitter {
public:
    void sendTextAsBinary(const String text);
    void encryptAndSendTextAsBinary(const String text, const EncryptionAlgo algo, const String key);
    void initTransmitter(const DtlpTransmitterConfig dtlpTransmitterConfig);

private:
    const uint8_t _handshakeSignalMilliseconds = 100;
    Encryptor* _encryptor = new Encryptor;
    uint8_t _bitDurationMilliseconds = 30;
    uint8_t _transmittersPins[8];

    void _sendHandshakeSignal();
    byte* _textToBin(const String& s);
};

#endif
