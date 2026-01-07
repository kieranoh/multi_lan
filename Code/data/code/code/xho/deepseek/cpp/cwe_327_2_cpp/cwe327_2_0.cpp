#include <openssl/evp.h>
#include <openssl/err.h>
#include <memory>
#include <stdexcept>

encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // 키 길이 검증 (최소 64바이트 필요)
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes");
    }
    
    encryption_result result;
    
    // AES-256-CBC 사용 (32바이트 키 필요)
    const int KEY_LENGTH = 32;
    const int IV_LENGTH = AES_BLOCK_SIZE;
    
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
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)> ctx(
        EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);
    
    if (!ctx) {
        throw std::runtime_error("Failed to create cipher context");
    }
    
    // AES-256-CBC 암호화 초기화
    if (EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), nullptr,
                          result.key.data(), result.iv.data()) != 1) {
        throw std::runtime_error("Failed to initialize encryption");
    }
    
    // 출력 버퍼 준비 (패딩을 위한 추가 공간 포함)
    result.encrypted_data.resize(padded_data.size() + AES_BLOCK_SIZE);
    
    int out_len = 0;
    int final_len = 0;
    
    // 데이터 암호화
    if (EVP_EncryptUpdate(ctx.get(), result.encrypted_data.data(), &out_len,
                         padded_data.data(), static_cast<int>(padded_data.size())) != 1) {
        throw std::runtime_error("Encryption failed");
    }
    
    // 최종 블록 처리
    if (EVP_EncryptFinal_ex(ctx.get(), result.encrypted_data.data() + out_len, &final_len) != 1) {
        throw std::runtime_error("Final encryption failed");
    }
    
    // 실제 암호화된 데이터 크기로 조정
    result.encrypted_data.resize(out_len + final_len);
    
    return result;
}