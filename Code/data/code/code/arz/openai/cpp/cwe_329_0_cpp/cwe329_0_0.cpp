#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// PKCS7에 따라 데이터를 패딩하는 헬퍼 함수입니다.
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* AES 및 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 길어야 합니다 (>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용하세요.
암호화된 데이터, IV(초기화 벡터), 및 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성하는 바이트
@param data 암호화할 데이터
@return 튜플 포함: {암호화된 데이터, IV, 암호화에 사용된 키} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < AES_BLOCK_SIZE) {
        throw std::invalid_argument("Key must be at least 16 bytes long.");
    }
    
    // AES 블록 크기
    const size_t block_size = AES_BLOCK_SIZE;
    
    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, block_size);
    
    // IV 초기화
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Failed to generate IV.");
    }
    
    // AES 암호화 설정
    AES_KEY encrypt_key;
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // 키의 첫 16 바이트를 사용
    AES_set_encrypt_key(key.data(), 128, &encrypt_key);
    
    // CBC 모드로 데이터 암호화
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);
    
    return std::make_tuple(encrypted_data, iv, std::vector<uint8_t>(key.begin(), key.begin() + AES_BLOCK_SIZE));
}