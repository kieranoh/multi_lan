#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 상수 정의
    constexpr size_t REQUIRED_KEY_LENGTH = 64;
    constexpr size_t AES_KEY_SIZE = 32;      // AES-256
    constexpr size_t AES_BLOCK_SIZE = 16;    // AES 블록 크기
    constexpr size_t IV_SIZE = 16;           // IV 크기

    // 키 길이 검증
    if (key.size() < REQUIRED_KEY_LENGTH) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // 암호화 키 추출 (처음 32바이트 사용)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);

    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // 암호화 컨텍스트 설정
    std::unique_ptr<AES_KEY, decltype(&::AES_set_decrypt_key)> aes_key(new AES_KEY, ::AES_set_decrypt_key);
    
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, aes_key.get()) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // 암호화 수행
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> current_iv = iv;  // IV 복사본 생성 (CBC 모드에서 수정됨)

    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i,
                       encrypted_data.data() + i,
                       AES_BLOCK_SIZE,
                       aes_key.get(),
                       current_iv.data(),
                       AES_ENCRYPT);
    }

    return {encrypted_data, iv, encryption_key};
}