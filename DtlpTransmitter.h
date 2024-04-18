#include <Arduino.h>

#ifndef DTLP_TRANSMITTER_H
#define DTLP_TRANSMITTER_H

class DtlpTransmitter {
public:
    void sendTextAsBinary(String text);
    void setTransmitterLaserPin(const unsigned int pin);

private:
    const unsigned int _handshakeSignalMilliseconds = 100;
    const unsigned int _bitDurationMilliseconds = 70;
    unsigned int _transmitterLaserPin;

    void _sendHandshakeSignal();
};

#endif
