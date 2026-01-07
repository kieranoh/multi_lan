#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

// 根据PKCS7填充数据的辅助函数
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* 使用AES和CBC模式对数据进行加密。提供的密钥字节长度足够（>= 64字节）。使用与所需长度匹配的提供的密钥字节的前缀。返回加密数据、IV（初始化向量）和用于加密的密钥。

@param key 生成加密密钥的字节
@param data 要加密的数据
@return 包含：{加密数据，IV，用于加密的密钥}的元组 */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) { // 确保密钥长度至少为256位
        throw std::invalid_argument("Key must be at least 32 bytes long for AES-256.");
    }

    // 初始化AES上下文
    AES_KEY enc_key;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    
    // 生成随机IV
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    // 使用前32个字节作为AES密钥
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + 32);
    
    // 填充数据
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // 输出加密数据
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // 设置加密密钥
    AES_set_encrypt_key(aes_key.data(), 256, &enc_key);
    
    // CBC模式加密
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &enc_key, iv.data(), AES_ENCRYPT);
    
    return {encrypted_data, iv, aes_key};
}