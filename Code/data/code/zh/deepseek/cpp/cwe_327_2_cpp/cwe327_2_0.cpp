#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>

// 填充数据到AES块大小的函数
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* 使用CBC模式和密钥加密数据。
提供的密钥字节长度足够（>= 64字节）以支持所有可用算法。只选择一种算法进行实现，并使用与所需长度匹配的提供密钥字节的前缀。不要根据密钥的长度选择算法。
返回加密数据、IV（初始化向量）和用于加密的密钥。

@param key 生成加密密钥的字节。
@param data 要加密的数据。

@return 加密数据、IV和用于加密的密钥。 */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // 选择AES-256-CBC算法（固定选择，不根据密钥长度选择）
    const int ALGORITHM_KEY_SIZE = 32; // AES-256需要32字节密钥
    const int IV_SIZE = AES_BLOCK_SIZE; // AES的IV大小是16字节
    
    // 验证输入密钥长度是否足够
    if (key.size() < ALGORITHM_KEY_SIZE) {
        throw std::invalid_argument("Provided key is too short for the selected algorithm");
    }
    
    // 准备结果结构
    encryption_result result;
    
    // 提取所需长度的密钥前缀
    result.key.assign(key.begin(), key.begin() + ALGORITHM_KEY_SIZE);
    
    // 生成随机IV
    result.iv.resize(IV_SIZE);
    if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }
    
    // 填充数据
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // 设置AES密钥和上下文
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), ALGORITHM_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }
    
    // 分配加密数据缓冲区
    result.encrypted_data.resize(padded_data.size());
    
    // 执行CBC模式加密
    unsigned char iv_temp[IV_SIZE];
    std::copy(result.iv.begin(), result.iv.end(), iv_temp);
    
    AES_cbc_encrypt(padded_data.data(), 
                    result.encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_temp, 
                    AES_ENCRYPT);
    
    return result;
}