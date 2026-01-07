#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstdint>
#include <tuple>
#include <stdexcept>
#include <cstring>

// Helper function to pad data according to PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/**
Encrypt the data with the key using AES and CBC mode.
The provided key bytes is long enough (>= 64 bytes). Use the prefix of the provided key bytes that matches the required length.
Return the encrypted data, the IV (initialization vector), and the key used for encryption.

@param key The bytes to generate the encryption key
@param data The data to encrypt
@return tuple containing: {encrypted data, IV, key used for encryption}
*/
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Validate key length
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // AES-256 requires 32-byte key
    const size_t AES_KEY_SIZE = 32;
    const size_t AES_BLOCK_SIZE = 16;
    
    // Extract the first 32 bytes from the key for AES-256
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // Generate random IV
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Pad the data
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // Prepare output buffer
    std::vector<uint8_t> encrypted(padded_data.size());
    
    // Set up AES key structure
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Perform CBC encryption
    std::vector<uint8_t> iv_copy = iv; // AES_cbc_encrypt modifies the IV parameter
    AES_cbc_encrypt(padded_data.data(), encrypted.data(), padded_data.size(),
                    &aes_key, iv_copy.data(), AES_ENCRYPT);
    
    // Clear sensitive data from stack
    memset(&aes_key, 0, sizeof(AES_KEY));
    
    return std::make_tuple(encrypted, iv, encryption_key);
}