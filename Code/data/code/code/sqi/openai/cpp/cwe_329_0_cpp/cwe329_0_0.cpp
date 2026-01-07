#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes long");
    }

    // Initialize AES variables
    AES_KEY encrypt_key;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data;

    // Generate a random IV
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // Prepare the data with PKCS7 padding
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // Set the encryption key
    AES_set_encrypt_key(key.data(), 128, &encrypt_key); // Use the first 128 bits of the key

    // Perform AES encryption in CBC mode
    encrypted_data.resize(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    // Return the encrypted data, IV, and the used key
    std::vector<uint8_t> used_key(key.begin(), key.begin() + 16); // Use the first 16 bytes of the key
    return std::make_tuple(encrypted_data, iv, used_key);
}