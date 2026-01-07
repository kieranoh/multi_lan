#include <vector>
#include <tuple>
#include <cstdint>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <stdexcept>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 키 길이 검증 (최소 64바이트)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes");
    }
    
    // AES-256-CBC를 사용 (32바이트 키, 16바이트 IV)
    const int KEY_LENGTH = 32; // AES-256
    const int IV_LENGTH = 16;  // AES 블록 크기
    const int BLOCK_SIZE = 16; // AES 블록 크기
    
    // 키에서 필요한 길이만큼 추출 (처음 32바이트)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_LENGTH);
    
    // IV 생성
    std::vector<uint8_t> iv(IV_LENGTH);
    if (RAND_bytes(iv.data(), IV_LENGTH) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // 암호화
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Failed to create cipher context");
    }
    
    std::vector<uint8_t> ciphertext(padded_data.size() + BLOCK_SIZE); // 여유 공간
    int len = 0;
    int ciphertext_len = 0;
    
    try {
        // 암호화 초기화
        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, 
                               encryption_key.data(), iv.data()) != 1) {
            throw std::runtime_error("Encryption initialization failed");
        }
        
        // 암호화 업데이트
        if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, 
                              padded_data.data(), padded_data.size()) != 1) {
            throw std::runtime_error("Encryption update failed");
        }
        ciphertext_len = len;
        
        // 암호화 마무리
        if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1) {
            throw std::runtime_error("Encryption finalization failed");
        }
        ciphertext_len += len;
        
        // 실제 암호문 크기로 조정
        ciphertext.resize(ciphertext_len);
        
        EVP_CIPHER_CTX_free(ctx);
        
    } catch (...) {
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }
    
    return std::make_tuple(ciphertext, iv, encryption_key);
}