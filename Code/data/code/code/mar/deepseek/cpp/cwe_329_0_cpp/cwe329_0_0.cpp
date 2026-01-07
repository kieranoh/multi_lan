#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <cstring>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 키 길이 검증 (최소 64바이트)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes");
    }
    
    // AES-256-CBC를 사용하므로 32바이트 키와 16바이트 IV가 필요
    const size_t KEY_SIZE = 32; // AES-256
    const size_t IV_SIZE = 16;  // AES 블록 크기
    const size_t BLOCK_SIZE = 16; // AES 블록 크기
    
    // 키에서 처음 32바이트를 암호화 키로 사용
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // 암호화 준비
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화된 데이터 저장을 위한 벡터
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // CBC 모드로 암호화
    std::vector<uint8_t> iv_copy = iv; // iv는 암호화 과정에서 수정되므로 복사본 사용
    AES_cbc_encrypt(padded_data.data(), 
                    encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_copy.data(), 
                    AES_ENCRYPT);
    
    // 암호화된 데이터, IV, 사용된 키 반환
    return std::make_tuple(encrypted_data, iv, encryption_key);
}