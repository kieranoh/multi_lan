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
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // AES-256-CBC를 사용하기 위해 32바이트 키 추출
    const size_t AES_KEY_SIZE = 32; // AES-256
    const size_t AES_BLOCK_SIZE = 16; // AES 블록 크기
    
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // IV 생성 (16바이트)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 암호화된 데이터를 저장할 벡터
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // CBC 모드로 암호화
    std::vector<uint8_t> ivec = iv; // IV 복사 (AES_cbc_encrypt이 수정함)
    
    AES_cbc_encrypt(
        padded_data.data(),
        encrypted_data.data(),
        padded_data.size(),
        &aes_key,
        ivec.data(),
        AES_ENCRYPT
    );
    
    // 메모리 정리를 위해 키 지우기 (보안)
    OPENSSL_cleanse(&aes_key, sizeof(aes_key));
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}