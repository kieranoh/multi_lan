#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 상수 정의
    constexpr size_t AES_KEY_SIZE = 32; // AES-256 사용
    constexpr size_t AES_BLOCK_SIZE = 16; // AES 블록 크기
    constexpr size_t IV_SIZE = 16; // IV 크기 (AES 블록 크기와 동일)

    // 키 길이 검증
    if (key.size() < 64) {
        throw std::invalid_argument("Key bytes must be at least 64 bytes long");
    }

    // AES 키 생성 (제공된 키의 처음 32바이트 사용)
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + AES_KEY_SIZE);

    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // 암호화된 데이터를 저장할 벡터
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES 컨텍스트 설정
    std::unique_ptr<AES_KEY, decltype(&::AES_set_decrypt_key)> aes_ctx(new AES_KEY, ::AES_set_decrypt_key);
    
    if (AES_set_encrypt_key(aes_key.data(), AES_KEY_SIZE * 8, aes_ctx.get()) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // CBC 모드로 암호화
    std::vector<uint8_t> prev_block = iv;
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // 현재 블록 추출
        std::vector<uint8_t> current_block(padded_data.begin() + i, 
                                          padded_data.begin() + i + AES_BLOCK_SIZE);
        
        // CBC 모드: 평문 블록과 이전 암호문 블록 XOR
        for (size_t j = 0; j < AES_BLOCK_SIZE; ++j) {
            current_block[j] ^= prev_block[j];
        }

        // AES 암호화
        std::vector<uint8_t> encrypted_block(AES_BLOCK_SIZE);
        AES_encrypt(current_block.data(), encrypted_block.data(), aes_ctx.get());
        
        // 결과 저장
        std::copy(encrypted_block.begin(), encrypted_block.end(), 
                  encrypted_data.begin() + i);
        
        // 다음 블록을 위해 현재 암호문 블록 저장
        prev_block = encrypted_block;
    }

    return std::make_tuple(encrypted_data, iv, aes_key);
}