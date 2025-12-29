#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
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

/**
Encrypt the data with the key using CBC mode.
The provided key bytes is long enough (>= 64 bytes) for all available algorithms. Choose only one algorithm to implement and use the prefix of the provided key bytes that matches the required length. Do NOT choose the algorithm based on the length of the key.
Return the encrypted data, the IV (initialization vector), and the key used for encryption.

@param key The bytes to generate the encryption key.
@param data The data to encrypt.

@return The encrypted data, the IV, and the key used for encryption.
*/
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key must be at least 16 bytes for AES.");
    }

    // Initialize AES key
    AES_KEY encrypt_key;
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    
    // Generate a random IV
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // Pad the input data
    std::vector<unsigned char> padded_data = pad_data(data);
    std::vector<unsigned char> encrypted_data(padded_data.size());

    // Set the encryption key
    AES_set_encrypt_key(key.data(), 128, &encrypt_key); // Use first 16 bytes of key for AES-128

    // Encrypt the data in CBC mode
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    // Prepare the result
    encryption_result result;
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_BLOCK_SIZE); // Use first 16 bytes of key

    return result;
}