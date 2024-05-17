#include "DtlpReceiver.h"

void DtlpReceiver::_initVars() {
  _startSignalProcessingStartedAt = 0;
  _processingStartSignal = false;
  _inActiveConnection = false;
  _lastSignalReceivedAt = 0;
  _endSignalFirstBitReceivedAt = 0;
  _lastBitRecordedAt = 0;
  _differenceInMillisecondsBetweenTimeOfTwoSignals = 0;
  _receivedData = "";
  _receivedBinary = "";
  _receiverStatus = ConnectionStatus::INACTIVE_CONNECTION;
}

void DtlpReceiver::_handleIncomingSignal(const bool byte[8]) {  // TODO: change attr to bool
  if (_lastBitRecordedAt == 0) {
    _lastBitRecordedAt = millis();
  }

  if (millis() - _lastBitRecordedAt >= _bitDurationMilliseconds) {  // init the whole bin, then convert to ASCII(speed up)
    _receivedBinary += byte[0];
    _receivedBinary += byte[1];
    _receivedBinary += byte[2];
    _receivedBinary += byte[3];
    _receivedBinary += byte[4];
    _receivedBinary += byte[5];
    _receivedBinary += byte[6];
    _receivedBinary += byte[7];

    _lastBitRecordedAt = millis();
  }
}

String DtlpReceiver::_binaryToAscii(String binaryString) {
    String result = "";

    // Loop through the binary string, parsing 8 characters at a time
    for (unsigned int i = 0; i < binaryString.length(); i += 8) {
        String byteString = binaryString.substring(i, i + 8);

        // In Arduino, if the receiver is not receiving a signal, it might return 1 instead of 0, so we swap 0 to 1 and 1 to 0
        for (int j = 0; j < 8; j++) {
            byteString[j] = (byteString[j] == '0') ? '1' : '0';
        }

        char byte = strtol(byteString.c_str(), NULL, 2);  // Convert binary string to char
        result += byte;  // Add the character to the result string
    }

    return result;
}


void DtlpReceiver::handleProcessorInterator(const bool byte[8]) {
  if (!_inActiveConnection) {
    if (! byte[0]) { // in arduino if the receiver (photodiode or photoresistor) is not receiving a signal - returns 1 instead of 0, so do the reverse check
      if (!_processingStartSignal) {
        _receiverStatus = ConnectionStatus::PROCESSING_HANDSHAKE_SIGNAL;
        _processingStartSignal = true;
        _startSignalProcessingStartedAt = millis();
      } else if (millis() - _startSignalProcessingStartedAt >= _handshakeSignalMilliseconds) {
        _processingStartSignal = false;
        _inActiveConnection = true;
        _receiverStatus = ConnectionStatus::ACTIVE_CONNECTION;
        _lastReceivedData = "";
        _receivedBinary = "";
      }
    } else {
      _processingStartSignal = false;
    }

  } else {
    bool isEmptyByte = true;

    for (int i = 0; i < 8; i++) {
      if (byte[i] == 0) { // in arduino if the receiver (photodiode or photoresistor) is not receiving a signal - returns 1 instead of 0, so do the reverse check
          isEmptyByte = false;
          break;
      }
    }

    if(isEmptyByte) {
      _lastReceivedData = _receivedBinary;  // Save the data of latest successfull signal before reseting the object
      _initVars();
    }
    else {
      _handleIncomingSignal(byte);
    }
  }
}

uint8_t DtlpReceiver::status() {
  return _receiverStatus;
}

String DtlpReceiver::getReceivedData() {
  return _binaryToAscii(_lastReceivedData);
}

void DtlpReceiver::initReceiver(const DtlpReceiverConfig dtlpReceiverConfig) {
  _bitDurationMilliseconds = dtlpReceiverConfig.bitDurationMilliseconds;
  _initVars();
}

String DtlpReceiver::decryptAndGetReceivedData(const EncryptionAlgo algo, const String key) {
  return _encryptor->decrypt(_lastReceivedData, algo, key);
}