#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// PKCS7에 따라 데이터를 패딩하는 헬퍼 함수
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* AES와 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용합니다.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트
@param data 암호화할 데이터
@return 튜플: {암호화된 데이터, IV, 암호화에 사용된 키} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key size must be at least 32 bytes.");
    }

    // 블록 크기 및 패딩
    const size_t block_size = AES_BLOCK_SIZE;
    std::vector<uint8_t> padded_data = pkcs7_pad(data, block_size);

    // IV 생성
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // 암호화 초기화
    AES_KEY enc_key;
    if (AES_set_encrypt_key(key.data(), 256, &enc_key) != 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    // 암호화
    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += block_size) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, block_size, &enc_key, iv.data(), AES_ENCRYPT);
    }

    // 사용된 키에 대한 접두사 (32 바이트 길이)
    std::vector<uint8_t> used_key(key.begin(), key.begin() + 32);

    return {encrypted_data, iv, used_key};
}