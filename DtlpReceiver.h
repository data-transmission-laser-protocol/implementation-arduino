#include <Arduino.h>
#include "EncryptionAlgo.h"
#include "Encryptor.h"

#ifndef DTLP_RECEIVER_H
#define DTLP_RECEIVER_H

typedef struct {
    uint8_t bitDurationMilliseconds;
} DtlpReceiverConfig;

enum ConnectionStatus {
    PROCESSING_HANDSHAKE_SIGNAL,
    ACTIVE_CONNECTION,
    INACTIVE_CONNECTION
};

class DtlpReceiver {
public:  
  void handleProcessorInterator(const uint8_t signalValue);
  void initReceiver(const DtlpReceiverConfig dtlpReceiverConfig);

  uint8_t status();
  String getReceivedData();
  String decryptAndGetReceivedData(const EncryptionAlgo algo, const String key);

private:
  const uint8_t _handshakeSignalMilliseconds = 100;
  Encryptor* _encryptor = new Encryptor;
  uint8_t _bitDurationMilliseconds = 30;

  unsigned long _startSignalProcessingStartedAt;
  bool _processingStartSignal;
  bool _inActiveConnection;
  String _receivedBinary;
  String _receivedData;
  String _lastReceivedData;
  unsigned long _lastSignalReceivedAt;
  unsigned long _endSignalFirstBitReceivedAt;
  unsigned long _lastBitRecordedAt;
  unsigned int _bitsCount;
  unsigned int _differenceInMillisecondsBetweenTimeOfTwoSignals;
  unsigned int _receiverStatus;

  void _initVars();
  unsigned int _handleIncomingSignal(bool bit);
  String _binaryToAscii(String binaryString);
};

#endif
