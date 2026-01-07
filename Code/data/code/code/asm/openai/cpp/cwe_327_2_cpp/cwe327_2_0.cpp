#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>

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
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_BLOCK_SIZE); // Use first 16 bytes for AES

    // Perform AES encryption in CBC mode
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(result.key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set encryption key");
    }

    std::vector<unsigned char> encrypted_data(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);
    
    result.encrypted_data = encrypted_data;

    return result;
}