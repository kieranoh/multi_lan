#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>

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

    // 초기화 벡터(IV) 생성
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate random IV");
    }
    result.iv = iv;

    // AES 암호화 준비
    AES_KEY aes_key;
    std::vector<unsigned char> padded_data = pad_data(data);

    // AES 키 설정 (AES-128, AES-192, AES-256 중 하나 선택)
    if (key.size() >= 16) {
        AES_set_encrypt_key(key.data(), 128, &aes_key);
    } else {
        throw std::runtime_error("Key size is insufficient for AES encryption");
    }

    // 암호화 데이터 버퍼
    result.encrypted_data.resize(padded_data.size());

    // CBC 모드로 암호화
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    // 암호화에 사용된 키는 제공된 키의 접두사로 사용
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // 16바이트 키 사용

    return result;
}