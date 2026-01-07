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

/* AES와 CBC 모드를 사용하여 키로 데이터를 암호화합니다.
제공된 키 바이트는 충분히 깁니다(>= 64 바이트). 필요한 길이에 맞는 제공된 키 바이트의 접두사를 사용합니다.
암호화된 데이터, IV(초기화 벡터), 암호화에 사용된 키를 반환합니다.

@param key 암호화 키를 생성할 바이트
@param data 암호화할 데이터
@return 튜플: {암호화된 데이터, IV, 암호화에 사용된 키} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 16) {
        throw std::invalid_argument("Key must be at least 16 bytes long");
    }

    // AES 블록 크기와 IV 크기 설정
    const size_t AES_BLOCK_SIZE = 16;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    
    // 랜덤 IV 생성
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }

    // 데이터 패딩
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 암호화된 데이터 저장소
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // AES 암호화 설정
    AES_KEY encrypt_key;
    std::vector<uint8_t> key_prefix(key.begin(), key.begin() + 16); // 첫 16바이트 사용
    AES_set_encrypt_key(key_prefix.data(), 128, &encrypt_key); // 128 비트 키 사용

    // CBC 모드로 암호화
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR하고 암호화
        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            if (i == 0) {
                encrypted_data[i + j] = padded_data[i + j] ^ iv[j];
            } else {
                encrypted_data[i + j] = padded_data[i + j] ^ encrypted_data[i - AES_BLOCK_SIZE + j];
            }
        }
        AES_encrypt(encrypted_data.data() + i, encrypted_data.data() + i, &encrypt_key);
    }

    return std::make_tuple(encrypted_data, iv, key_prefix);
}