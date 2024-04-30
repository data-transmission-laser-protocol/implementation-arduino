#include <Arduino.h>
#include "Encryptor.h"

String Encryptor::encrypt(const String text, const EncryptionAlgo algo, const String key) {
	if(algo == EncryptionAlgo::XOR) {
		return _encryptXOR(text, key);
	}
	else {
		return _encryptXOR(text, key);	// avoid compiler warning
	}
}

String Encryptor::decrypt(const String cipherText, const EncryptionAlgo algo, const String key) {
	if(algo == EncryptionAlgo::XOR) {
		return _decryptXOR(cipherText, key);
	}
	else {
		return _decryptXOR(cipherText, key);  // avoid compiler warning
	}
}

String Encryptor::_encryptXOR(const String text, const String key) {
	  String encryptedData = "";

    // Convert the key to a C-style string
    const char* keyStr = key.c_str();

    for (size_t i = 0; i < text.length(); ++i) {
        // XOR each character of the text with the corresponding character of the key
        encryptedData += char(text[i] ^ keyStr[i % key.length()]);
    }

    return encryptedData;
}

String Encryptor::_decryptXOR(const String ciphertext, const String key) {
    String decryptedData = "";

    const char* keyStr = key.c_str();
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char decryptedChar = ciphertext[i] ^ keyStr[i % key.length()]; // Perform XOR operation
        decryptedData += decryptedChar; // Append the decrypted character directly
    }

    return decryptedData;
}