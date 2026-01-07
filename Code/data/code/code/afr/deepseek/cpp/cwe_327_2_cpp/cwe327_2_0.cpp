#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
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
    // 입력 검증
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }

    encryption_result result;
    
    // AES-256-CBC를 사용 (키 길이: 32바이트, IV 길이: 16바이트)
    const int AES_KEY_LENGTH = 32; // 256비트
    const int AES_IV_LENGTH = AES_BLOCK_SIZE; // 16바이트
    
    // 키 준비: 제공된 키에서 AES_KEY_LENGTH 바이트 사용
    result.key.resize(AES_KEY_LENGTH);
    size_t key_copy_size = std::min(key.size(), static_cast<size_t>(AES_KEY_LENGTH));
    std::copy_n(key.begin(), key_copy_size, result.key.begin());
    
    // 키가 충분히 길지 않으면 나머지를 0으로 채움
    if (key_copy_size < AES_KEY_LENGTH) {
        std::fill(result.key.begin() + key_copy_size, result.key.end(), 0);
    }
    
    // IV 생성
    result.iv.resize(AES_IV_LENGTH);
    if (RAND_bytes(result.iv.data(), AES_IV_LENGTH) != 1) {
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
    std::vector<unsigned char> prev_block(AES_BLOCK_SIZE);
    std::copy(result.iv.begin(), result.iv.end(), prev_block.begin());
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // CBC 모드: 평문 블록과 이전 암호문 블록 XOR
        std::vector<unsigned char> xor_block(AES_BLOCK_SIZE);
        for (int j = 0; j < AES_BLOCK_SIZE; ++j) {
            xor_block[j] = padded_data[i + j] ^ prev_block[j];
        }
        
        // AES 암호화
        AES_encrypt(xor_block.data(), &result.encrypted_data[i], &aes_key);
        
        // 현재 암호문 블록을 다음 블록의 XOR에 사용
        std::copy(&result.encrypted_data[i], &result.encrypted_data[i] + AES_BLOCK_SIZE, prev_block.begin());
    }
    
    return result;
}