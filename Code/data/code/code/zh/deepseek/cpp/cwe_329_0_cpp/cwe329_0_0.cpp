#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstdint>
#include <tuple>
#include <stdexcept>
#include <cstring>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // 验证密钥长度
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes long");
    }

    // 使用密钥的前32字节作为AES-256密钥
    const size_t AES_KEY_SIZE = 32; // AES-256
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);

    // 生成16字节的IV
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // 使用PKCS7填充数据
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // 创建AES上下文
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // 分配加密数据缓冲区
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // 执行CBC模式加密
    std::vector<uint8_t> iv_copy = iv; // 需要可修改的副本
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), &aes_key, iv_copy.data(), AES_ENCRYPT);

    // 返回加密数据、IV和使用的密钥
    return std::make_tuple(encrypted_data, iv, encryption_key);
}