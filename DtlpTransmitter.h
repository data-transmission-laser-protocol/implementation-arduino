#include <Arduino.h>
#include "EncryptionAlgo.h"
#include "Encryptor.h"

#ifndef DTLP_TRANSMITTER_H
#define DTLP_TRANSMITTER_H

typedef struct {
    uint8_t bitDurationMilliseconds;
    uint8_t transmitterLaserPin;
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
    unsigned int _transmitterLaserPin;

    void _sendHandshakeSignal();
};

#endif
