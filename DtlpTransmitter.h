#include <Arduino.h>

#ifndef DTLP_TRANSMITTER_H
#define DTLP_TRANSMITTER_H

typedef struct {
    uint8_t bitDurationMilliseconds;
    uint8_t transmitterLaserPin;
} DtlpTransmitterConfig;

class DtlpTransmitter {
public:
    void sendTextAsBinary(String text);
    void initTransmitter(const DtlpTransmitterConfig dtlpTransmitterConfig);

private:
    const uint8_t _handshakeSignalMilliseconds = 100;
    uint8_t _bitDurationMilliseconds = 30;

    unsigned int _transmitterLaserPin;

    void _sendHandshakeSignal();
};

#endif
