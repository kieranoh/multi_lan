#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 키 길이 검증
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes");
    }

    // AES-256-CBC를 사용 (256비트 = 32바이트)
    const size_t KEY_SIZE = 32;
    const size_t BLOCK_SIZE = AES_BLOCK_SIZE;
    
    // 키 접두사 추출
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(BLOCK_SIZE);
    if (RAND_bytes(iv.data(), BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // 암호화 준비
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // CBC 모드로 암호화
    std::vector<uint8_t> ivec = iv; // IV 복사 (AES_cbc_encrypt이 수정함)
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(),
                    padded_data.size(), &aes_key, ivec.data(), AES_ENCRYPT);
    
    // 결과 반환
    return {encrypted_data, iv, encryption_key};
}