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
        throw std::invalid_argument("Key must be at least 32 bytes long.");
    }

    // 사용될 키의 접두사 생성 (32바이트)
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + 32);

    // AES 블록 크기 및 초기화 벡터(IV) 설정
    const size_t block_size = AES_BLOCK_SIZE;
    std::vector<uint8_t> iv(block_size);
    if (!RAND_bytes(iv.data(), block_size)) {
        throw std::runtime_error("Failed to generate IV.");
    }

    // 데이터를 PKCS7 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, block_size);

    // AES 암호화 초기화
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key.data(), 256, &encrypt_key) < 0) {
        throw std::runtime_error("Failed to set encryption key.");
    }

    // 암호화된 데이터를 저장할 벡터
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES-CBC 암호화
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    // 결과 반환
    return std::make_tuple(encrypted_data, iv, aes_key);
}