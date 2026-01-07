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
    constexpr size_t AES_KEY_SIZE = 32; // AES-256
    constexpr size_t AES_BLOCK_SIZE = 16;
    constexpr size_t IV_SIZE = AES_BLOCK_SIZE;
    
    // 키 길이 검증
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least " + std::to_string(AES_KEY_SIZE) + " bytes");
    }
    
    // 실제 암호화에 사용할 키 추출 (첫 AES_KEY_SIZE 바이트)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 암호화 컨텍스트 설정
    std::unique_ptr<AES_KEY, decltype(&::AES_set_encrypt_key)> aes_key(new AES_KEY, ::AES_set_encrypt_key);
    
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, aes_key.get()) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화된 데이터 저장소
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // CBC 모드 암호화 수행
    std::vector<uint8_t> iv_copy = iv; // iv는 수정되므로 복사본 사용
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), aes_key.get(), iv_copy.data(), AES_ENCRYPT);
    
    return {encrypted_data, iv, encryption_key};
}