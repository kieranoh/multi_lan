#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <stdexcept>
#include <memory>

// PKCS7에 따라 데이터를 패딩하는 헬퍼 함수
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* AES와 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용합니다.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트
@param data 암호화할 데이터
@return 튜플: {암호화된 데이터, IV, 암호화에 사용된 키} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 키 길이 검증
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes");
    }
    
    // AES-256-CBC를 사용 (256비트 = 32바이트)
    const size_t KEY_SIZE = 32;
    const size_t BLOCK_SIZE = 16;
    const size_t IV_SIZE = 16;
    
    // 키 추출 (처음 32바이트 사용)
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + KEY_SIZE);
    
    // IV 생성
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, BLOCK_SIZE);
    
    // 암호화 컨텍스트 생성
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&EVP_CIPHER_CTX_free)> ctx(
        EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);
    
    if (!ctx) {
        throw std::runtime_error("Failed to create cipher context");
    }
    
    // 암호화 초기화
    if (EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), nullptr, 
                          encryption_key.data(), iv.data()) != 1) {
        throw std::runtime_error("Failed to initialize encryption");
    }
    
    // 암호화 수행
    std::vector<uint8_t> ciphertext(padded_data.size() + BLOCK_SIZE);
    int out_len = 0;
    int total_len = 0;
    
    // 데이터 암호화
    if (EVP_EncryptUpdate(ctx.get(), ciphertext.data(), &out_len, 
                         padded_data.data(), static_cast<int>(padded_data.size())) != 1) {
        throw std::runtime_error("Encryption update failed");
    }
    total_len = out_len;
    
    // 최종 암호화 블록 처리
    if (EVP_EncryptFinal_ex(ctx.get(), ciphertext.data() + total_len, &out_len) != 1) {
        throw std::runtime_error("Encryption finalization failed");
    }
    total_len += out_len;
    
    // 실제 암호문 크기로 조정
    ciphertext.resize(total_len);
    
    return std::make_tuple(ciphertext, iv, encryption_key);
}