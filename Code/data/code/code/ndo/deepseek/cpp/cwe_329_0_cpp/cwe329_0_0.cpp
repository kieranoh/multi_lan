#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 상수 정의
    constexpr size_t AES_KEY_SIZE = 32; // AES-256
    constexpr size_t AES_BLOCK_SIZE = 16;
    constexpr size_t IV_SIZE = AES_BLOCK_SIZE;

    // 키 길이 검증
    if (key.size() < AES_KEY_SIZE) {
        throw std::invalid_argument("Key must be at least " + std::to_string(AES_KEY_SIZE) + " bytes");
    }

    // 실제 암호화에 사용할 키 추출 (첫 AES_KEY_SIZE 바이트)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);

    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // 암호화 준비
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // 암호화 수행
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> prev_block = iv;

    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // CBC 모드: 현재 블록을 이전 암호문 블록과 XOR
        std::vector<uint8_t> xor_block(AES_BLOCK_SIZE);
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            xor_block[j] = padded_data[i + j] ^ prev_block[j];
        }

        // AES 암호화
        AES_encrypt(xor_block.data(), &encrypted_data[i], &aes_key);
        
        // 현재 암호문 블록을 다음 블록의 이전 블록으로 설정
        std::copy(&encrypted_data[i], &encrypted_data[i + AES_BLOCK_SIZE], prev_block.begin());
    }

    return {encrypted_data, iv, encryption_key};
}

// PKCS7 패딩 함수 (주어진 함수 시그니처에 맞게)
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}