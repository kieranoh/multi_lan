#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstring>

// Funktion zum Auffüllen von Daten auf die AES-Blockgröße
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, static_cast<unsigned char>(padding));

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
    // Wähle AES-256-CBC als Algorithmus (festgelegt, nicht basierend auf Schlüssellänge)
    constexpr int ALGORITHM_KEY_SIZE = 32; // 256 bits für AES-256
    constexpr int IV_SIZE = AES_BLOCK_SIZE; // 128 bits für AES
    
    // Überprüfe, ob der Schlüssel lang genug ist
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("Schlüssel ist zu kurz für AES-256");
    }
    
    // Extrahiere die ersten ALGORITHM_KEY_SIZE Bytes als Schlüssel
    std::vector<unsigned char> encryption_key(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // Generiere IV (Initialisierungsvektor)
    std::vector<unsigned char> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Fehler bei der Generierung des IV");
    }
    
    // Padd die Daten für AES-Blockverschlüsselung
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Initialisiere den AES-Kontext
    std::unique_ptr<AES_KEY, decltype(&::AES_set_decrypt_key)> aes_key(new AES_KEY, ::AES_set_decrypt_key);
    
    // Setze den Verschlüsselungsschlüssel
    if (AES_set_encrypt_key(encryption_key.data(), ALGORITHM_KEY_SIZE * 8, aes_key.get()) != 0) {
        throw std::runtime_error("Fehler beim Setzen des AES-Schlüssels");
    }
    
    // Verschlüssele die Daten im CBC-Modus
    std::vector<unsigned char> encrypted_data(padded_data.size());
    std::vector<unsigned char> current_iv = iv; // Kopie für die Verschlüsselung
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR mit IV oder vorherigem Block
        for (int j = 0; j < AES_BLOCK_SIZE; ++j) {
            padded_data[i + j] ^= current_iv[j];
        }
        
        // AES-Verschlüsselung
        AES_encrypt(&padded_data[i], &encrypted_data[i], aes_key.get());
        
        // Aktualisiere IV für nächsten Block
        std::memcpy(current_iv.data(), &encrypted_data[i], AES_BLOCK_SIZE);
    }
    
    // Erstelle das Ergebnis
    encryption_result result;
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::move(encryption_key);
    
    return result;
}