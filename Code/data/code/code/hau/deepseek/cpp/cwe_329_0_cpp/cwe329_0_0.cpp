#include <openssl/evp.h>
#include <openssl/err.h>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <cstring>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 1. 키 길이 검증 및 AES-256 키 추출 (32바이트 = 256비트)
    if (key.size() < 32) {
        throw std::invalid_argument("Key must be at least 32 bytes for AES-256");
    }
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + 32);
    
    // 2. IV 생성 (16바이트 = 128비트 블록 크기)
    std::vector<uint8_t> iv(EVP_CIPHER_iv_length(EVP_aes_256_cbc()));
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV");
    }
    
    // 3. 데이터 패딩 (PKCS7)
    const size_t block_size = EVP_CIPHER_block_size(EVP_aes_256_cbc());
    std::vector<uint8_t> padded_data = pkcs7_pad(data, block_size);
    
    // 4. 암호화 컨텍스트 설정
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Failed to create cipher context");
    }
    
    // 5. 암호화 초기화
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, 
                                aes_key.data(), iv.data())) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encryption initialization failed");
    }
    
    // 6. 암호화 수행
    std::vector<uint8_t> ciphertext(padded_data.size() + block_size);
    int out_len = 0;
    int total_len = 0;
    
    if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &out_len, 
                               padded_data.data(), padded_data.size())) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encryption update failed");
    }
    total_len = out_len;
    
    // 7. 최종 블록 처리
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + total_len, &out_len)) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Encryption finalization failed");
    }
    total_len += out_len;
    
    // 8. 실제 암호문 크기로 조정
    ciphertext.resize(total_len);
    
    // 9. 정리
    EVP_CIPHER_CTX_free(ctx);
    
    return {ciphertext, iv, aes_key};
}

// PKCS7 패딩 함수 (문제에 이미 제공됨)
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}