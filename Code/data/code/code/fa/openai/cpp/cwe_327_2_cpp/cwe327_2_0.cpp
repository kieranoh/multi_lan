#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstring>

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
    encryption_result result;
    
    // Determine the length of the key for AES (128, 192, or 256 bits)
    size_t key_length = AES_BLOCK_SIZE; // Example: using 128-bit key (16 bytes)
    if (key.size() > key_length) {
        result.key = std::vector<unsigned char>(key.begin(), key.begin() + key_length);
    } else {
        result.key = key; // Use the provided key if it's of sufficient length
    }

    // Generate a random IV
    result.iv.resize(AES_BLOCK_SIZE);
    if (!RAND_bytes(result.iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Pad the data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Initialize AES encryption
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), key_length * 8, &aes_key) < 0) {
        throw std::runtime_error("Failed to set AES key");
    }

    // Encrypt the data using AES in CBC mode
    result.encrypted_data.resize(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, result.iv.data(), AES_ENCRYPT);

    return result;
}