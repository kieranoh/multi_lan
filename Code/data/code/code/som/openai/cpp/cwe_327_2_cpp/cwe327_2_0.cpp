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

/* CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 깁니다(>= 64 바이트). 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 암호화에 사용된 키입니다. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;
    
    // Generate a random IV
    result.iv.resize(AES_BLOCK_SIZE);
    if (!RAND_bytes(result.iv.data(), result.iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }

    // Prepare the key for AES
    unsigned char aes_key[AES_BLOCK_SIZE]; // AES key can be 128, 192 or 256 bits
    std::copy(key.begin(), key.begin() + AES_BLOCK_SIZE, aes_key);

    // Pad data
    std::vector<unsigned char> padded_data = pad_data(data);
    result.encrypted_data.resize(padded_data.size());

    // AES encryption in CBC mode
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, 128, &encrypt_key); // Assuming 128-bit key

    // Perform the encryption
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &encrypt_key, result.iv.data(), AES_ENCRYPT);

    // Store the key used (the same as the provided key in this case)
    result.key.assign(aes_key, aes_key + AES_BLOCK_SIZE);

    return result;
}