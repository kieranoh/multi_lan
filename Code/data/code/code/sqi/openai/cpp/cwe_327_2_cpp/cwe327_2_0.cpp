#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

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

encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key must be at least 32 bytes for AES-256.");
    }

    // Generate IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random bytes for IV.");
    }

    // Prepare padded data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Set up AES encryption
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(key.data(), 256, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key.");
    }

    // Encrypt data
    std::vector<unsigned char> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(
            padded_data.data() + i,
            encrypted_data.data() + i,
            AES_BLOCK_SIZE,
            &encrypt_key,
            iv.data(),
            AES_ENCRYPT
        );
    }

    return {encrypted_data, iv, std::vector<unsigned char>(key.begin(), key.begin() + 32)};
}