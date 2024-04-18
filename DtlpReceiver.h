#include <Arduino.h>

#ifndef DTLP_RECEIVER_H
#define DTLP_RECEIVER_H

class DtlpReceiver {
public:
  enum ConnectionStatus {
    PROCESSING_HANDSHAKE_SIGNAL,
    ACTIVE_CONNECTION,
    INACTIVE_CONNECTION
  };
  
  void handleProcessorInterator(const unsigned int signalValue);
  unsigned int status();
  String getReceivedData();

  DtlpReceiver();


private:
  const unsigned long _handshakeSignalMilliseconds = 100;
  const unsigned int _bitDurationMilliseconds = 70;
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
