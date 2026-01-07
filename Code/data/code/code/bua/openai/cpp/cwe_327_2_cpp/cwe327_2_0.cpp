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
    result.iv.resize(AES_BLOCK_SIZE);
    if (!RAND_bytes(result.iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Could not generate IV");
    }

    // Prepare the key (AES requires a key length of 128, 192, or 256 bits)
    std::vector<unsigned char> aes_key(key.begin(), key.begin() + 16); // Using the first 16 bytes for AES-128

    // Pad the data
    std::vector<unsigned char> padded_data = pad_data(data);

    // Set up AES encryption
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key.data(), 128, &encrypt_key);

    // Encrypt the data
    result.encrypted_data.resize(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, result.encrypted_data.data() + i,
                        AES_BLOCK_SIZE, &encrypt_key, result.iv.data(), AES_ENCRYPT);
    }

    // Store the key used for encryption (for the sake of the return structure)
    result.key = aes_key;

    return result;
}