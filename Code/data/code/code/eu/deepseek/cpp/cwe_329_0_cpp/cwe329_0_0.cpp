#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Konstanteak definitu
    const size_t AES_BLOCK_SIZE = 16;
    const size_t KEY_SIZE = 32; // AES-256 erabiliko dugu
    
    // Gakoaren tamaina egiaztatu
    if (key.size() < KEY_SIZE) {
        throw std::invalid_argument("Gakoak gutxienez " + std::to_string(KEY_SIZE) + " byte izan behar ditu");
    }
    
    // Gakoa moztu behar den tamainara (AES-256)
    std::vector<uint8_t> actual_key(key.begin(), key.begin() + KEY_SIZE);
    
    // IV sortu (Initialization Vector)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Ezin izan da IV segurua sortu");
    }
    
    // Datuak PKCS7 padding aplikatu
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // Enkriptatutako datuentzat bufferra prestatu
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // AES kontextua hasieratu
    AES_KEY aes_key;
    if (AES_set_encrypt_key(actual_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Ezin izan da AES gakoa hasieratu");
    }
    
    // CBC moduan enkriptatu
    std::vector<uint8_t> iv_copy = iv; // AES_cbc_encrypt-ek IV aldatu dezake
    AES_cbc_encrypt(
        padded_data.data(),
        encrypted_data.data(),
        padded_data.size(),
        &aes_key,
        iv_copy.data(),
        AES_ENCRYPT
    );
    
    // Enkriptatutako datuak, IV eta erabilitako gakoa itzuli
    return std::make_tuple(encrypted_data, iv, actual_key);
}