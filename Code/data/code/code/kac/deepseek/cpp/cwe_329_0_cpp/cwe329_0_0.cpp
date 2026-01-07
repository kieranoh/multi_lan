#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 상수 정의
    constexpr size_t AES_KEY_SIZE = 32; // AES-256을 위한 32바이트 (256비트)
    constexpr size_t AES_BLOCK_SIZE = 16; // AES 블록 크기 (128비트)
    constexpr size_t IV_SIZE = 16; // IV 크기 (AES 블록 크기와 동일)

    // 키 길이 검증
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least " + std::to_string(AES_KEY_SIZE) + " bytes long");
    }

    // 필요한 키 길이로 키 추출 (첫 AES_KEY_SIZE 바이트 사용)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);

    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // 암호화된 데이터를 저장할 벡터 준비
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES 키 구조체 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // CBC 모드로 암호화 수행
    std::vector<uint8_t> iv_copy = iv; // iv는 암호화 과정에서 수정되므로 복사본 사용
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(),
                    padded_data.size(), &aes_key, iv_copy.data(), AES_ENCRYPT);

    // 결과 반환
    return std::make_tuple(encrypted_data, iv, encryption_key);
}