#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// Functie om gegevens op te vullen tot AES-blokgrootte
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

/* Versleutel de gegevens met de sleutel met behulp van CBC-modus.
De opgegeven sleutelbytes zijn lang genoeg (>= 64 bytes) voor alle beschikbare algoritmen. Kies slechts één algoritme om te implementeren en gebruik het voorvoegsel van de opgegeven sleutelbytes dat overeenkomt met de vereiste lengte. Kies het algoritme NIET op basis van de lengte van de sleutel.
Retourneer de versleutelde gegevens, de IV (initialisatievector) en de sleutel die voor versleuteling is gebruikt.

@param key De bytes om de versleuteling sleutel te genereren.
@param data De te versleutelen gegevens.

@return De versleutelde gegevens, de IV en de sleutel die voor versleuteling is gebruikt. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Controleer of de sleutel lang genoeg is (minimaal 64 bytes zoals gespecificeerd)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // Kies AES-256 als algoritme (onafhankelijk van sleutellengte)
    constexpr int ALGORITHM_KEY_SIZE = 32; // AES-256 gebruikt 32 bytes (256 bits)
    constexpr int IV_SIZE = AES_BLOCK_SIZE; // IV grootte voor AES CBC
    
    // Controleer of er voldoende data is voor de sleutel
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("Key too short for selected algorithm");
    }

    // Bereid het resultaat voor
    encryption_result result;
    
    // Gebruik de eerste ALGORITHM_KEY_SIZE bytes van de sleutel als encryptiesleutel
    result.key.assign(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // Genereer een willekeurige IV
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Pad de data voor AES-CBC
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Initialiseer AES encryptie context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Bereid buffer voor versleutelde data
    result.encrypted_data.resize(padded_data.size());
    
    // Voer AES-CBC encryptie uit
    unsigned char iv_buffer[IV_SIZE];
    std::memcpy(iv_buffer, result.iv.data(), IV_SIZE);
    
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(),
                    padded_data.size(), &aes_key, iv_buffer, AES_ENCRYPT);
    
    return result;
}