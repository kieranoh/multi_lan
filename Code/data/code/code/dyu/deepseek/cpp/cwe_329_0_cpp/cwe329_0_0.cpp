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
    
    // 키 추출 (처음 AES_KEY_SIZE 바이트 사용)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), static_cast<int>(iv.size())) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 암호화 준비
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), 256, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화 수행
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> prev_block = iv;
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // 현재 평문 블록
        std::vector<uint8_t> plain_block(padded_data.begin() + i, 
                                        padded_data.begin() + i + AES_BLOCK_SIZE);
        
        // CBC 모드: 평문 블록과 이전 암호문 블록 XOR
        std::vector<uint8_t> xored_block(AES_BLOCK_SIZE);
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            xored_block[j] = plain_block[j] ^ prev_block[j];
        }
        
        // AES 암호화
        std::vector<uint8_t> cipher_block(AES_BLOCK_SIZE);
        AES_encrypt(xored_block.data(), cipher_block.data(), &aes_key);
        
        // 결과 저장
        std::copy(cipher_block.begin(), cipher_block.end(), 
                 encrypted_data.begin() + i);
        
        // 다음 블록을 위해 현재 암호문 블록 저장
        prev_block = cipher_block;
    }
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}