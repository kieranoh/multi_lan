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
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // AES-128 사용
    result.iv.resize(AES_BLOCK_SIZE);
    RAND_bytes(result.iv.data(), result.iv.size());

    std::vector<unsigned char> padded_data = pad_data(data);
    result.encrypted_data.resize(padded_data.size());

    AES_KEY aes_key;
    AES_set_encrypt_key(result.key.data(), 128, &aes_key);
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, result.encrypted_data.data() + i, AES_BLOCK_SIZE, &aes_key, result.iv.data(), AES_ENCRYPT);
    }

    return result;
}