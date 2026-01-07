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
        throw std::runtime_error("Unable to generate random IV");
    }
    result.iv = iv;

    // Prepare the key (use first 16 bytes for AES)
    std::vector<unsigned char> aes_key(key.begin(), key.begin() + 16);
    
    // Pad the data
    std::vector<unsigned char> padded_data = pad_data(data);
    size_t data_len = padded_data.size();

    // Initialize AES encryption
    AES_KEY aes_enc_key;
    AES_set_encrypt_key(aes_key.data(), 128, &aes_enc_key);

    // Encrypt data
    result.encrypted_data.resize(data_len);
    for (size_t i = 0; i < data_len; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(
            padded_data.data() + i,
            result.encrypted_data.data() + i,
            AES_BLOCK_SIZE,
            &aes_enc_key,
            iv.data(),
            AES_ENCRYPT
        );
    }

    // Store the key used for encryption
    result.key = aes_key;

    return result;
}