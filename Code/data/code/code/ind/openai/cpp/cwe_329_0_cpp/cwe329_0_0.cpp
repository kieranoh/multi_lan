#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>

// PKCS7에 따라 데이터를 패딩하는 도우미 함수입니다.
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
    // AES 블록 크기 및 IV 크기 정의
    const size_t block_size = AES_BLOCK_SIZE;
    const size_t key_size = 32; // AES-256을 사용

    // 키 길이에 맞는 키 생성 (접두사)
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + key_size);

    // IV를 위한 버퍼 생성
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("IV 생성 실패");
    }

    // 데이터를 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, block_size);

    // AES 암호화 초기화
    AES_KEY encrypt_key;
    if (AES_set_encrypt_key(aes_key.data(), 256, &encrypt_key) < 0) {
        throw std::runtime_error("암호화 키 설정 실패");
    }

    // 암호화된 데이터를 저장할 버퍼 생성
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES CBC 모드 암호화
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &encrypt_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, aes_key);
}