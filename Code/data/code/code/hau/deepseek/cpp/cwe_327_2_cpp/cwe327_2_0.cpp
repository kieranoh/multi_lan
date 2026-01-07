#include <openssl/evp.h>
#include <openssl/err.h>
#include <stdexcept>
#include <string>

encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // 입력 유효성 검사
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes");
    }
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }

    encryption_result result;
    
    // AES-256-CBC를 사용 (32바이트 키 필요)
    const int KEY_LENGTH = 32;
    const int IV_LENGTH = 16; // AES 블록 크기
    
    // 키의 처음 32바이트를 AES-256 키로 사용
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + KEY_LENGTH);
    
    // IV 생성 (16바이트)
    result.iv.resize(IV_LENGTH);
    if (RAND_bytes(result.iv.data(), IV_LENGTH) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }
    
    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // 암호화 컨텍스트 생성
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Failed to create cipher context");
    }
    
    try {
        // AES-256-CBC 암호화 초기화
        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, 
                              result.key.data(), result.iv.data()) != 1) {
            throw std::runtime_error("Failed to initialize encryption");
        }
        
        // 암호화 수행
        result.encrypted_data.resize(padded_data.size() + EVP_CIPHER_CTX_block_size(ctx));
        int out_len = 0;
        int final_len = 0;
        
        // 데이터 암호화
        if (EVP_EncryptUpdate(ctx, result.encrypted_data.data(), &out_len,
                             padded_data.data(), (int)padded_data.size()) != 1) {
            throw std::runtime_error("Failed to encrypt data");
        }
        
        // 최종 블록 암호화
        if (EVP_EncryptFinal_ex(ctx, result.encrypted_data.data() + out_len, &final_len) != 1) {
            throw std::runtime_error("Failed to finalize encryption");
        }
        
        // 실제 암호화된 데이터 크기로 조정
        result.encrypted_data.resize(out_len + final_len);
        
        // 컨텍스트 정리
        EVP_CIPHER_CTX_free(ctx);
        
    } catch (...) {
        EVP_CIPHER_CTX_free(ctx);
        throw;
    }
    
    return result;
}