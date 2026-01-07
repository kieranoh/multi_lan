#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key size must be at least 32 bytes.");
    }

    // AES 기본 설정
    AES_KEY aes_key;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    
    // 랜덤 IV 생성
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // AES 키 설정
    if (AES_set_encrypt_key(key.data(), 256, &aes_key) < 0) {
        throw std::runtime_error("Failed to set AES encryption key.");
    }

    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES CBC 모드로 데이터 암호화
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), 
                    &aes_key, iv.data(), AES_ENCRYPT);

    // 암호화된 데이터와 IV, 키 반환
    return {encrypted_data, iv, std::vector<uint8_t>(key.begin(), key.begin() + 32)};
}