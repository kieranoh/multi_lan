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
    padded_data.resize(padded_len, static_cast<unsigned char>(padding));

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
    // 입력 유효성 검사
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }

    encryption_result result;

    // AES-256-CBC를 사용 (제공된 키 바이트가 충분히 길다고 가정)
    constexpr int AES_256_KEY_SIZE = 32; // 256비트 = 32바이트
    constexpr int AES_BLOCK_SIZE = 16;   // 128비트 블록 크기

    // 키 생성: 제공된 키의 처음 32바이트 사용
    if (key.size() < AES_256_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least 32 bytes for AES-256");
    }
    result.key.assign(key.begin(), key.begin() + AES_256_KEY_SIZE);

    // IV 생성 (16바이트)
    result.iv.resize(AES_BLOCK_SIZE);
    if (RAND_bytes(result.iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);

    // 암호화된 데이터 버퍼 준비
    result.encrypted_data.resize(padded_data.size());

    // AES 컨텍스트 설정
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), AES_256_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // CBC 모드로 암호화
    unsigned char iv_buffer[AES_BLOCK_SIZE];
    std::memcpy(iv_buffer, result.iv.data(), AES_BLOCK_SIZE);

    AES_cbc_encrypt(
        padded_data.data(),
        result.encrypted_data.data(),
        padded_data.size(),
        &aes_key,
        iv_buffer,
        AES_ENCRYPT
    );

    // 보안을 위해 키 메모리 정리 (선택사항)
    OPENSSL_cleanse(&aes_key, sizeof(aes_key));
    OPENSSL_cleanse(iv_buffer, sizeof(iv_buffer));

    return result;
}