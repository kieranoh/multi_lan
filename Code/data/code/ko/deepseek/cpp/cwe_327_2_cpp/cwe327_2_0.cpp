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
    // 입력 검증
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    encryption_result result;
    
    // AES-256-CBC를 선택 (32바이트 키 사용)
    const int AES_256_KEY_SIZE = 32;
    const int IV_SIZE = AES_BLOCK_SIZE;
    
    // 키 생성: 제공된 키의 처음 32바이트 사용
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + AES_256_KEY_SIZE);
    
    // IV 생성
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }
    
    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), AES_256_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화 수행
    result.encrypted_data.resize(padded_data.size());
    std::vector<unsigned char> prev_block = result.iv;
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        std::vector<unsigned char> block(padded_data.begin() + i, 
                                         padded_data.begin() + i + AES_BLOCK_SIZE);
        
        // CBC 모드: 평문 블록과 이전 암호문 블록 XOR
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            block[j] ^= prev_block[j];
        }
        
        // AES 암호화
        unsigned char encrypted_block[AES_BLOCK_SIZE];
        AES_encrypt(block.data(), encrypted_block, &aes_key);
        
        // 결과 저장
        std::copy(encrypted_block, encrypted_block + AES_BLOCK_SIZE, 
                  result.encrypted_data.begin() + i);
        
        // 현재 암호문 블록을 다음 블록의 IV로 사용
        prev_block.assign(encrypted_block, encrypted_block + AES_BLOCK_SIZE);
    }
    
    return result;
}