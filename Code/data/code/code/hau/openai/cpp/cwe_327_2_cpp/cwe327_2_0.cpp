#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>

// 데이터 패딩 함수
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

/* CBC 모드를 사용하여 AES로 데이터를 암호화합니다. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);

    // 초기화 벡터 생성
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // AES 암호화 설정
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // 암호화된 데이터 저장소
    std::vector<unsigned char> encrypted_data(padded_data.size());

    // CBC 모드로 데이터 암호화
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    // 결과 반환
    encryption_result result;
    result.encrypted_data = encrypted_data;
    result.iv = iv;
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // AES-128 사용
    return result;
}