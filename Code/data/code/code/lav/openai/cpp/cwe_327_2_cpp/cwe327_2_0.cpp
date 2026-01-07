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

/* CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 길이(>= 64 바이트)입니다. 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하는 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 및 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;
    std::vector<unsigned char> padded_data = pad_data(data);

    // Generate a random IV
    result.iv.resize(AES_BLOCK_SIZE);
    if (!RAND_bytes(result.iv.data(), result.iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Configure AES encryption
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set encryption key");
    }

    // Encrypt the data
    result.encrypted_data.resize(padded_data.size());
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &encrypt_key, result.iv.data(), AES_ENCRYPT);

    // Copy the key to result (use the first 16 bytes for AES-128)
    result.key.assign(key.begin(), key.begin() + 16);

    return result;
}