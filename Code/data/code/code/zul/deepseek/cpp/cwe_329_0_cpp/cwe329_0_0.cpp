#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <cstring>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 상수 정의
    const size_t AES_KEY_SIZE = 32; // AES-256을 위한 32바이트 (256비트)
    const size_t AES_BLOCK_SIZE = 16; // AES 블록 크기 (128비트)
    
    // 키 길이 검증
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("키는 최소 " + std::to_string(AES_KEY_SIZE) + " 바이트 이상이어야 합니다.");
    }
    
    // 필요한 키 길이만큼 키 추출 (AES-256을 위해 32바이트)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // IV 생성 (16바이트)
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("IV 생성 실패");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 암호화 컨텍스트 생성
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("암호화 컨텍스트 생성 실패");
    }
    
    // 암호화 초기화 (AES-256-CBC)
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, 
                          encryption_key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("암호화 초기화 실패");
    }
    
    // 암호화 수행
    std::vector<uint8_t> ciphertext(padded_data.size() + AES_BLOCK_SIZE);
    int len = 0;
    int ciphertext_len = 0;
    
    // 데이터 암호화
    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, 
                         padded_data.data(), padded_data.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("암호화 실패");
    }
    ciphertext_len = len;
    
    // 최종 암호화 블록 처리
    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + ciphertext_len, &len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("암호화 최종화 실패");
    }
    ciphertext_len += len;
    
    // 실제 암호문 크기로 벡터 크기 조정
    ciphertext.resize(ciphertext_len);
    
    // 컨텍스트 정리
    EVP_CIPHER_CTX_free(ctx);
    
    return std::make_tuple(ciphertext, iv, encryption_key);
}