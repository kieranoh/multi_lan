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
    
    // AES-256-CBC를 사용 (256비트 키 = 32바이트)
    const int AES_KEY_LENGTH = 32; // AES-256
    const int IV_LENGTH = AES_BLOCK_SIZE;
    
    // 키의 처음 32바이트를 AES-256 키로 사용
    std::vector<unsigned char> aes_key(key.begin(), key.begin() + AES_KEY_LENGTH);
    result.key = aes_key;
    
    // IV 생성
    std::vector<unsigned char> iv(IV_LENGTH);
    if (RAND_bytes(iv.data(), IV_LENGTH) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    result.iv = iv;
    
    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // AES 컨텍스트 설정
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key.data(), AES_KEY_LENGTH * 8, &aes_ctx) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 암호화 수행
    std::vector<unsigned char> encrypted_data(padded_data.size());
    std::vector<unsigned char> current_iv = iv;
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // CBC 모드: 평문 블록과 IV/XOR
        std::vector<unsigned char> xor_block(AES_BLOCK_SIZE);
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            xor_block[j] = padded_data[i + j] ^ current_iv[j];
        }
        
        // AES 암호화
        AES_encrypt(xor_block.data(), encrypted_data.data() + i, &aes_ctx);
        
        // 다음 블록을 위한 IV 업데이트
        memcpy(current_iv.data(), encrypted_data.data() + i, AES_BLOCK_SIZE);
    }
    
    result.encrypted_data = encrypted_data;
    return result;
}