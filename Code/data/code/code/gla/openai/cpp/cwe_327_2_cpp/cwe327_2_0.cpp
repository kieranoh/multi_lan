#include <openssl/aes.h>
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
    if (key.size() < 16) {
        throw std::invalid_argument("Key size must be at least 16 bytes for AES.");
    }

    // Generate a random IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate IV.");
    }

    // Pad data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Initialize AES encryption
    AES_KEY enc_key;
    if (AES_set_encrypt_key(key.data(), 128, &enc_key) != 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    std::vector<unsigned char> encrypted_data(padded_data.size());

    // Perform AES CBC encryption
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &enc_key, iv.data(), AES_ENCRYPT);

    // Prepare the result
    encryption_result result;
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // Use the first 16 bytes of the key

    return result;
}