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
    encryption_result result;
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Init initialization vector (IV)
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }
    result.iv = iv;

    // Determine encryption algorithm based on key size
    if (key.size() >= 32) { // AES-256
        AES_KEY aes_key;
        AES_set_encrypt_key(key.data(), 256, &aes_key);
        result.encrypted_data.resize(padded_data.size());
        AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);
    } 
    else if (key.size() >= 24) { // AES-192
        AES_KEY aes_key;
        AES_set_encrypt_key(key.data(), 192, &aes_key);
        result.encrypted_data.resize(padded_data.size());
        AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);
    } 
    else if (key.size() >= 16) { // AES-128
        AES_KEY aes_key;
        AES_set_encrypt_key(key.data(), 128, &aes_key);
        result.encrypted_data.resize(padded_data.size());
        AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);
    } 
    else {
        throw std::invalid_argument("Key size is too small. Must be at least 16 bytes.");
    }

    result.key = key; // Store the original key used for encryption
    return result;
}