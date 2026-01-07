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
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes long.");
    }

    // AES 초기화
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(key.data(), 128, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // 암호화
    std::vector<uint8_t> encrypted_data(padded_data.size());
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data.data() + i, encrypted_data.data() + i, AES_BLOCK_SIZE, &encrypt_key, iv.data(), AES_ENCRYPT);
    }

    // 키의 접두사로 사용할 16바이트 반환
    std::vector<uint8_t> used_key(key.begin(), key.begin() + 16);

    return std::make_tuple(encrypted_data, iv, used_key);
}