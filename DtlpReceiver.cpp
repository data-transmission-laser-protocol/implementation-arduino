
#include "DtlpReceiver.h"

void DtlpReceiver::_initVars() {
  _startSignalProcessingStartedAt = 0;
  _processingStartSignal = false;
  _inActiveConnection = false;
  _receivedBinary = "";
  _lastSignalReceivedAt = 0;
  _endSignalFirstBitReceivedAt = 0;
  _lastBitRecordedAt = 0;
  _bitsCount = 0;
  _differenceInMillisecondsBetweenTimeOfTwoSignals = 0;
  _receivedData = "";
  _receiverStatus = ConnectionStatus::INACTIVE_CONNECTION;
}

unsigned int DtlpReceiver::_handleIncomingSignal(bool bit) {  // TODO: change attr to bool
  if (_lastBitRecordedAt == 0) {
    _lastBitRecordedAt = millis();
  }

  if (millis() - _lastBitRecordedAt >= _bitDurationMilliseconds) {
    _receivedBinary += String(bit);
    _bitsCount++;

    if (_bitsCount == 8) {
      if (_receivedBinary == "00000000") {
        return ConnectionStatus::INACTIVE_CONNECTION;
      }
      _receivedData += _binaryToAscii(_receivedBinary);
      _receivedBinary = "";
      _bitsCount = 0;
    }

    _lastBitRecordedAt = millis();
  }

  return ConnectionStatus::ACTIVE_CONNECTION;
}

String DtlpReceiver::_binaryToAscii(String binaryString) {
  String result = "";

  // Loop through the binary string, parsing 8 characters at a time
  for (unsigned int i = 0; i < binaryString.length(); i += 8) {
    String byteString = binaryString.substring(i, i + 8);
    char byte = strtol(byteString.c_str(), NULL, 2);  // Convert binary string to char

    result += byte;  // Add the character to the result string
  }

  return result;
}

void DtlpReceiver::handleProcessorInterator(const uint8_t signalValue) {
  if (!_inActiveConnection) {
    if (signalValue) {
      if (!_processingStartSignal) {
        _receiverStatus = ConnectionStatus::PROCESSING_HANDSHAKE_SIGNAL;
        _processingStartSignal = true;
        _startSignalProcessingStartedAt = millis();
      } else if (millis() - _startSignalProcessingStartedAt >= _handshakeSignalMilliseconds) {
        _processingStartSignal = false;
        _inActiveConnection = true;
        _receiverStatus = ConnectionStatus::ACTIVE_CONNECTION;
      }
    } else {
      _processingStartSignal = false;
    }

  } else {
    if (_handleIncomingSignal(signalValue) == ConnectionStatus::INACTIVE_CONNECTION) {
      _lastReceivedData = _receivedData;  // Save the data of latest successfull signal before reseting the object
      _initVars();
    }
  }
}

uint8_t DtlpReceiver::status() {
  return _receiverStatus;
}

String DtlpReceiver::getReceivedData() {
  return _lastReceivedData;
}

void DtlpReceiver::initReceiver(const DtlpReceiverConfig dtlpReceiverConfig) {
  _bitDurationMilliseconds = dtlpReceiverConfig.bitDurationMilliseconds;
  _initVars();
}