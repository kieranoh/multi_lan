#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <cstring>

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
    
    // AES 컨텍스트 초기화
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화된 데이터 저장을 위한 벡터 준비
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // CBC 모드로 암호화
    std::vector<uint8_t> prev_block = iv; // 첫 번째 블록의 이전 블록은 IV
    size_t num_blocks = padded_data.size() / AES_BLOCK_SIZE;
    
    for (size_t i = 0; i < num_blocks; ++i) {
        // 현재 평문 블록
        const uint8_t* plaintext_block = padded_data.data() + i * AES_BLOCK_SIZE;
        
        // XOR: 평문 블록 ⊕ 이전 암호문 블록 (첫 번째는 IV)
        std::vector<uint8_t> xor_block(AES_BLOCK_SIZE);
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            xor_block[j] = plaintext_block[j] ^ prev_block[j];
        }
        
        // AES 암호화
        uint8_t* ciphertext_block = encrypted_data.data() + i * AES_BLOCK_SIZE;
        AES_encrypt(xor_block.data(), ciphertext_block, &aes_key);
        
        // 다음 블록을 위해 현재 암호문 블록 저장
        prev_block.assign(ciphertext_block, ciphertext_block + AES_BLOCK_SIZE);
    }
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}