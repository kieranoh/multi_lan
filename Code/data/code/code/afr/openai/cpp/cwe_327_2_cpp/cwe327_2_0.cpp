#include <openssl/aes.h>
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
    AES_KEY aes_key;
    std::vector<unsigned char> iv(AES_BLOCK_SIZE);
    
    // IV 생성
    if (!RAND_bytes(iv.data(), AES_BLOCK_SIZE)) {
        throw std::runtime_error("Failed to generate IV");
    }

    // AES 키 설정 (128 비트 키 사용)
    if (AES_set_encrypt_key(key.data(), 128, &aes_key) < 0) {
        throw std::runtime_error("Failed to set AES key");
    }

    // 데이터 패딩
    std::vector<unsigned char> padded_data = pad_data(data);
    result.encrypted_data.resize(padded_data.size());

    // AES CBC 모드로 암호화
    AES_cbc_encrypt(padded_data.data(), result.encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    // 결과에 IV와 키 저장
    result.iv = iv;
    result.key = std::vector<unsigned char>(key.begin(), key.begin() + 16); // 128비트 키의 경우 앞 16바이트 사용

    return result;
}