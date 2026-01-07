#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>

// PKCS7에 따라 데이터를 패딩하는 헬퍼 함수
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* AES와 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트
@param data 암호화할 데이터
@return 튜플: {암호화된 데이터, IV, 암호화에 사용된 키} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // AES 블록 크기 및 CBC 모드 초기화
    const size_t AES_BLOCK_SIZE = AES_BLOCK_SIZE;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 키는 128비트, 192비트, 또는 256비트여야 하므로 적절한 길이로 자름
    std::vector<uint8_t> key_to_use(key.begin(), key.begin() + AES_BLOCK_SIZE);

    // 패딩된 데이터 준비
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 암호화
    std::vector<uint8_t> encrypted_data(padded_data.size());
    AES_KEY aes_key;
    AES_set_encrypt_key(key_to_use.data(), 128, &aes_key);

    // CBC 모드 암호화
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR with IV for the first block
        if (i == 0) {
            for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
                padded_data[i + j] ^= iv[j];
            }
        } else {
            for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
                padded_data[i + j] ^= encrypted_data[i - AES_BLOCK_SIZE + j];
            }
        }
        AES_encrypt(padded_data.data() + i, encrypted_data.data() + i, &aes_key);
    }

    return {encrypted_data, iv, key_to_use};
}