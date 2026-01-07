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
    constexpr size_t AES_BLOCK_SIZE = 16;
    
    // 키 길이 검증
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least " + std::to_string(AES_KEY_SIZE) + " bytes");
    }
    
    // 키 추출 (첫 AES_KEY_SIZE 바이트 사용)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), static_cast<int>(iv.size())) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 암호화 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), 
                           static_cast<int>(encryption_key.size() * 8), 
                           &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화 수행
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> current_iv = iv;
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        std::vector<uint8_t> block(padded_data.begin() + i, 
                                   padded_data.begin() + i + AES_BLOCK_SIZE);
        
        // CBC 모드 XOR
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            block[j] ^= current_iv[j];
        }
        
        // AES 암호화
        AES_encrypt(block.data(), encrypted_data.data() + i, &aes_key);
        
        // 다음 블록을 위한 IV 업데이트
        std::copy(encrypted_data.begin() + i, 
                  encrypted_data.begin() + i + AES_BLOCK_SIZE, 
                  current_iv.begin());
    }
    
    return {encrypted_data, iv, encryption_key};
}