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
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용합니다.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트
@param data 암호화할 데이터
@return 튜플: {암호화된 데이터, IV, 암호화에 사용된 키} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // AES 블록 크기 설정
    const size_t AES_BLOCK_SIZE = AES_BLOCK_SIZE;

    // 패딩된 데이터 생성
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate IV");
    }

    // 키의 적절한 길이로 자르기
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_BLOCK_SIZE);

    // AES 암호화 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Failed to set encryption key");
    }

    // 암호화된 데이터 버퍼 초기화
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES CBC 모드로 암호화 수행
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, encryption_key);
}