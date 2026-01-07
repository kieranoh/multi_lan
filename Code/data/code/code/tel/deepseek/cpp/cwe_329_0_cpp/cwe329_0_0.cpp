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
    constexpr size_t AES_KEY_SIZE = 32; // AES-256
    constexpr size_t AES_BLOCK_SIZE = 16; // AES 블록 크기
    constexpr size_t IV_SIZE = AES_BLOCK_SIZE; // IV 크기
    
    // 키 길이 검증
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least " + std::to_string(AES_KEY_SIZE) + " bytes");
    }
    
    // 실제 암호화에 사용할 키 추출 (첫 AES_KEY_SIZE 바이트)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), static_cast<int>(iv.size())) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), 
                           static_cast<int>(encryption_key.size() * 8), 
                           &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화된 데이터 저장소
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // CBC 모드로 암호화
    std::vector<uint8_t> ivec = iv; // IV 복사 (AES_cbc_encrypt이 수정함)
    
    AES_cbc_encrypt(padded_data.data(),
                   encrypted_data.data(),
                   padded_data.size(),
                   &aes_key,
                   ivec.data(),
                   AES_ENCRYPT);
    
    // 결과 반환
    return std::make_tuple(encrypted_data, iv, encryption_key);
}