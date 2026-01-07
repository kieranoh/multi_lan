#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 키 길이 검증
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // AES-256-CBC를 위한 키 및 IV 크기 정의
    const size_t AES_KEY_SIZE = 32; // 256비트
    const size_t AES_BLOCK_SIZE = 16; // 128비트
    const size_t IV_SIZE = AES_BLOCK_SIZE;

    // 키에서 필요한 만큼의 접두사 사용
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
        std::vector<uint8_t> block(padded_data.begin() + i, padded_data.begin() + i + AES_BLOCK_SIZE);
        
        // CBC 모드: 평문 블록과 이전 암호문 블록 XOR
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            block[j] ^= prev_block[j];
        }

        // AES 암호화
        AES_encrypt(block.data(), encrypted_data.data() + i, &aes_key);
        
        // 현재 암호문 블록을 다음 블록의 이전 블록으로 설정
        prev_block.assign(encrypted_data.begin() + i, encrypted_data.begin() + i + AES_BLOCK_SIZE);
    }

    return {encrypted_data, iv, encryption_key};
}