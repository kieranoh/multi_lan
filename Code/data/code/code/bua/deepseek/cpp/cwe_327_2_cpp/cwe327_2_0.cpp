#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstring>

// 데이터를 AES 블록 크기로 패딩하는 함수
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
제공된 키 바이트는 모든 사용 가능한 알고리즘에 대해 충분히 깁니다(>= 64 바이트). 구현할 알고리즘을 하나만 선택하고, 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요. 키의 길이에 따라 알고리즘을 선택하지 마세요.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트.
@param data 암호화할 데이터.

@return 암호화된 데이터, IV, 암호화에 사용된 키. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // 입력 유효성 검사
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }

    // AES-256-CBC를 선택 (키 길이: 32바이트, IV 길이: 16바이트)
    constexpr size_t AES_256_KEY_SIZE = 32;
    constexpr size_t AES_IV_SIZE = AES_BLOCK_SIZE;
    
    // 키 생성: 제공된 키의 처음 32바이트 사용
    std::vector<unsigned char> encryption_key(AES_256_KEY_SIZE);
    if (key.size() >= AES_256_KEY_SIZE) {
        std::copy(key.begin(), key.begin() + AES_256_KEY_SIZE, encryption_key.begin());
    } else {
        // 키가 충분하지 않으면 0으로 채움 (실제 환경에서는 더 안전한 방법 사용)
        std::copy(key.begin(), key.end(), encryption_key.begin());
        std::fill(encryption_key.begin() + key.size(), encryption_key.end(), 0);
    }

    // IV 생성
    std::vector<unsigned char> iv(AES_IV_SIZE);
    if (RAND_bytes(iv.data(), static_cast<int>(iv.size())) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // 암호화된 데이터를 저장할 벡터
    std::vector<unsigned char> encrypted_data(padded_data.size());

    // AES 컨텍스트 설정
    std::unique_ptr<AES_KEY, decltype(&::AES_set_decrypt_key)> aes_key(new AES_KEY, ::AES_set_decrypt_key);
    
    // AES 키 설정
    if (AES_set_encrypt_key(encryption_key.data(), AES_256_KEY_SIZE * 8, aes_key.get()) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // CBC 모드로 암호화
    std::vector<unsigned char> ivec = iv; // 복사본 생성 (AES_cbc_encrypt이 수정함)
    
    AES_cbc_encrypt(
        padded_data.data(),
        encrypted_data.data(),
        padded_data.size(),
        aes_key.get(),
        ivec.data(),
        AES_ENCRYPT
    );

    // 결과 반환
    encryption_result result;
    result.encrypted_data = std::move(encrypted_data);
    result.iv = std::move(iv);
    result.key = std::move(encryption_key);
    
    return result;
}