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

    // Generate a random IV
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }
    result.iv = iv;

    // Pad the data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Set up AES encryption
    AES_KEY aes_key;
    unsigned char aes_key_bytes[32]; // Maximum key size for AES
    std::memcpy(aes_key_bytes, key.data(), std::min(key.size(), sizeof(aes_key_bytes)));
    AES_set_encrypt_key(aes_key_bytes, 256, &aes_key); // Use AES-256 for encryption

    // Encrypt the data
    result.encrypted_data.resize(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(
            padded_data.data() + i,
            result.encrypted_data.data() + i,
            AES_BLOCK_SIZE,
            &aes_key,
            iv.data(),
            AES_ENCRYPT);
    }

    // Store the used key (first 32 bytes of the provided key)
    result.key.assign(aes_key_bytes, aes_key_bytes + 32);

    return result;
}