#include <Arduino.h>
#include "EncryptionAlgo.h"

#ifndef DTLP_ENCRYPTOR_H
#define DTLP_ENCRYPTOR_H

class Encryptor {
public:
    String encrypt(const String text, const EncryptionAlgo algo, const String key);
    String decrypt(const String cipherText, const EncryptionAlgo algo, const String key);

private:
    String _encryptXOR(const String text, const String key);
    String _decryptXOR(const String ciphertext, const String key);
};

#endif
