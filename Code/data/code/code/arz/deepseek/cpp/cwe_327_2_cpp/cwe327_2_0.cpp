#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

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
    
    // 키 길이 검증
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }
    
    // AES-256-CBC를 사용 (32바이트 키 필요)
    const int AES_KEY_SIZE = 32; // 256비트
    const int AES_IV_SIZE = AES_BLOCK_SIZE; // 16바이트
    
    // 키의 처음 32바이트를 AES 키로 사용
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("Key too short for AES-256");
    }
    
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // IV 생성
    result.iv.resize(AES_IV_SIZE);
    if (RAND_bytes(result.iv.data(), AES_IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화 수행
    result.encrypted_data.resize(padded_data.size());
    
    // IV 복사본 생성 (AES_cbc_encrypt이 IV를 수정함)
    std::vector<unsigned char> iv_copy = result.iv;
    
    AES_cbc_encrypt(
        padded_data.data(),
        result.encrypted_data.data(),
        padded_data.size(),
        &aes_key,
        iv_copy.data(),
        AES_ENCRYPT
    );
    
    return result;
}