#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

// Funkce pro vyplnění dat na velikost bloku AES
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

/* Zašifrujte data s klíčem pomocí režimu CBC.
Poskytnuté bajty klíče jsou dostatečně dlouhé (>= 64 bajtů) pro všechny dostupné algoritmy. Vyberte pouze jeden algoritmus k implementaci a použijte prefix poskytnutých bajtů klíče, který odpovídá požadované délce. NEvybírejte algoritmus na základě délky klíče.
Vrátí zašifrovaná data, IV (inicializační vektor) a klíč použitý pro šifrování.

@param key Bajty pro generování šifrovacího klíče.
@param data Data k zašifrování.

@return Zašifrovaná data, IV a klíč použitý pro šifrování. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Ověřte, že klíč je dostatečně dlouhý pro AES (16, 24 nebo 32 bajtů)
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes long.");
    }

    // Inicializace proměnných
    encryption_result result;
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // Používáme prvních 16 bajtů pro AES-128
    result.iv.resize(AES_BLOCK_SIZE); // Inicializační vektor

    // Generování náhodného IV
    if (RAND_bytes(result.iv.data(), result.iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Padded data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Inicializace AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key.");
    }

    // Zašifrování dat v režimu CBC
    result.encrypted_data.resize(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, result.iv.data(), AES_ENCRYPT);

    return result;
}