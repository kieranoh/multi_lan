#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

// Funktion zum Auffüllen von Daten auf die AES-Blockgröße
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* Verschlüssele die Daten mit dem Schlüssel im CBC-Modus.
Die bereitgestellten Schlüsselbytes sind lang genug (>= 64 Bytes) für alle verfügbaren Algorithmen. Wähle nur einen Algorithmus zur Implementierung und verwende das Präfix der bereitgestellten Schlüsselbytes, das der erforderlichen Länge entspricht. Wähle den Algorithmus NICHT basierend auf der Länge des Schlüssels.
Gib die verschlüsselten Daten, den IV (Initialisierungsvektor) und den für die Verschlüsselung verwendeten Schlüssel zurück.

@param key Die Bytes zur Generierung des Verschlüsselungsschlüssels.
@param data Die zu verschlüsselnden Daten.

@return Die verschlüsselten Daten, den IV und den für die Verschlüsselung verwendeten Schlüssel. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key length must be at least 16 bytes for AES.");
    }

    // Erstellen des AES-Schlüssels
    AES_KEY aes_key;
    if (AES_set_encrypt_key(key.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key.");
    }

    // Generieren des IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Padding der Daten
    std::vector<unsigned char> padded_data = pad_data(data);
    std::vector<unsigned char> encrypted_data(padded_data.size());

    // Verschlüsselung im CBC-Modus
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    // Rückgabe der Verschlüsselungsergebnisse
    return {encrypted_data, iv, std::vector<unsigned char>(key.begin(), key.begin() + AES_BLOCK_SIZE)};
}