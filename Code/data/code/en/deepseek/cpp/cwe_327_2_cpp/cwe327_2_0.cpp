#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// Function to pad data to AES block size
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
    // Choose AES-256-CBC algorithm (fixed choice as per requirements)
    const int KEY_SIZE = 32; // 256 bits for AES-256
    const int IV_SIZE = AES_BLOCK_SIZE; // 16 bytes for AES
    
    // Validate key length
    if (key.size() < KEY_SIZE) {
        throw std::invalid_argument("Provided key is too short for AES-256");
    }
    
    // Extract the first KEY_SIZE bytes for the encryption key
    std::vector<unsigned char> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // Generate random IV
    std::vector<unsigned char> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // Pad the data to AES block size
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Prepare encryption context
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // Prepare output buffer
    std::vector<unsigned char> encrypted_data(padded_data.size());
    
    // Create a copy of IV for CBC mode (will be modified during encryption)
    std::vector<unsigned char> iv_copy = iv;
    
    // Perform AES-CBC encryption
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, iv_copy.data(), AES_ENCRYPT);
    
    // Prepare and return result
    encryption_result result;
    result.encrypted_data = encrypted_data;
    result.iv = iv;
    result.key = encryption_key;
    
    return result;
}