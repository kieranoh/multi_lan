#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// Hilfsfunktion zum Auffüllen von Daten gemäß PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Verschlüssele die Daten mit dem Schlüssel unter Verwendung von AES und CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes). Verwende das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht.
Gib die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

@param key Die Bytes zur Generierung des Verschlüsselungsschlüssels
@param data Die zu verschlüsselnden Daten
@return Tuple mit: {verschlüsselte Daten, IV, verwendeter Schlüssel zur Verschlüsselung} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key must be at least 32 bytes long.");
    }
    
    // AES Schlüssel und IV initialisieren
    AES_KEY aes_key;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Daten aufblocken
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // Schlüssel für AES setzen (wir verwenden die ersten 32 Bytes des Schlüssels)
    std::vector<uint8_t> aes_key_bytes(key.begin(), key.begin() + 32);
    AES_set_encrypt_key(aes_key_bytes.data(), 256, &aes_key);

    // Verschlüsseln der Daten
    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, AES_BLOCK_SIZE, &aes_key, iv.data(), AES_ENCRYPT);
    }

    return { encrypted_data, iv, aes_key_bytes };
}