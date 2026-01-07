#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstring>

// AES 블록 크기에 맞게 데이터를 패딩하는 함수
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, static_cast<unsigned char>(padding));

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 길이(>= 64 바이트)입니다. 구현할 알고리즘은 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하는 바이트입니다.
@param data 암호화할 데이터입니다.

@return 암호화된 데이터, IV, 및 암호화에 사용된 키입니다. */
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
        throw std::invalid_argument("Key must be at least 64 bytes");
    }

    encryption_result result;
    
    // 알고리즘 선택: AES-256-CBC (키 길이 32바이트)
    constexpr size_t AES_256_KEY_SIZE = 32;
    constexpr size_t AES_IV_SIZE = AES_BLOCK_SIZE;
    
    // 키 접두사 추출
    result.key.assign(key.begin(), key.begin() + AES_256_KEY_SIZE);
    
    // IV 생성
    result.iv.resize(AES_IV_SIZE);
    if (RAND_bytes(result.iv.data(), AES_IV_SIZE) != 1) {
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
    std::vector<unsigned char> prev_block(result.iv.begin(), result.iv.end());
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // CBC 모드: 평문 블록과 이전 암호문 블록 XOR
        std::vector<unsigned char> xor_block(AES_BLOCK_SIZE);
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            xor_block[j] = padded_data[i + j] ^ prev_block[j];
        }
        
        // AES 암호화
        AES_encrypt(xor_block.data(), result.encrypted_data.data() + i, &aes_key);
        
        // 현재 암호문 블록을 다음 블록의 XOR 입력으로 설정
        std::memcpy(prev_block.data(), result.encrypted_data.data() + i, AES_BLOCK_SIZE);
    }
    
    return result;
}