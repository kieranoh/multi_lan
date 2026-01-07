#include <openssl/aes.h>
#include <openssl/rand.h>
#include <tuple>
#include <vector>
#include <stdexcept>

/**
 * Helper function to pad data based on PKCS7
 * 
 * @param data The data to be padded
 * @param block_size The size of the block to pad to
 * @return Padded data
 */
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/**
 * Encrypt data using AES with CBC mode with the provided key.
 * The provided key bytes should be sufficient (>= 64 bytes).
 * Use the key's prefix bytes that match the required length.
 * 
 * @param key Bytes for generating the encryption key
 * @param data The data to be encrypted
 * @return tuple containing: {encrypted data, IV, key used for encryption}
 */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>> encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {  // AES-256 requires a 32-byte key
        throw std::invalid_argument("Key size must be at least 32 bytes for AES-256.");
    }

    AES_KEY aes_key;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    
    // Generate a random IV
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Error generating random IV.");
    }

    // Use the first 32 bytes of the key
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + 32);

    // Pad the data
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // Set encryption key
    if (AES_set_encrypt_key(encryption_key.data(), 256, &aes_key) < 0) {
        throw std::runtime_error("Error setting encryption key.");
    }

    // Encrypt data in CBC mode
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}