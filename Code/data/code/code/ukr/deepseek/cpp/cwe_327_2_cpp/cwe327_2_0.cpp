#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>

std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    encryption_result result;
    
    // 입력 검증
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }
    
    // AES-256을 선택 (키 길이: 32바이트 = 256비트)
    const int AES_KEY_LENGTH = 32; // AES-256
    const int IV_LENGTH = AES_BLOCK_SIZE;
    
    // 키 생성: 제공된 키의 처음 32바이트 사용
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_KEY_LENGTH);
    
    // IV 생성
    result.iv.resize(IV_LENGTH);
    if (RAND_bytes(result.iv.data(), IV_LENGTH) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), AES_KEY_LENGTH * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화 수행
    result.encrypted_data.resize(padded_data.size());
    unsigned char iv_buffer[IV_LENGTH];
    std::copy(result.iv.begin(), result.iv.end(), iv_buffer);
    
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(),
                    padded_data.size(), &aes_key, iv_buffer, AES_ENCRYPT);
    
    return result;
}