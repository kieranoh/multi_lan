#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// 用于保存返回值的结构
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* 使用 AES 和 CBC 模式用密钥加密数据。
提供的密钥字节长度足够（>= 64 字节）。使用与所需长度匹配的提供密钥字节的前缀。
返回加密数据、IV（初始化向量）和用于加密的密钥。

@param key 生成加密密钥的字节。
@param data 要加密的数据。

@return 加密数据、IV 和用于加密的密钥。 */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    result.encrypted_data = NULL;
    result.encrypted_len = 0;
    result.iv = NULL;
    result.key = NULL;
    
    // 检查输入参数
    if (key == NULL || data == NULL || key_len < 64) {
        return result;
    }
    
    // 创建并初始化 AES 密钥结构
    AES_KEY aes_key;
    
    // 使用密钥的前 32 字节作为 AES-256 密钥
    unsigned char aes_key_bytes[32];
    memcpy(aes_key_bytes, key, 32);
    
    // 设置加密密钥
    if (AES_set_encrypt_key(aes_key_bytes, 256, &aes_key) != 0) {
        return result;
    }
    
    // 分配并生成随机 IV（16 字节用于 AES CBC）
    result.iv = (unsigned char*)malloc(16);
    if (result.iv == NULL) {
        return result;
    }
    
    if (RAND_bytes(result.iv, 16) != 1) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // 计算填充后的数据长度（PKCS#7 填充）
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // 分配内存用于填充后的数据和加密结果
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // 复制原始数据
    memcpy(padded_data, data, data_len);
    
    // 应用 PKCS#7 填充
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // 分配内存用于加密数据
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        free(padded_data);
        result.iv = NULL;
        return result;
    }
    
    // 执行 AES CBC 加密
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // 设置加密数据长度
    result.encrypted_len = padded_len;
    
    // 分配并复制使用的密钥
    result.key = (unsigned char*)malloc(32);
    if (result.key == NULL) {
        free(result.iv);
        free(padded_data);
        free(result.encrypted_data);
        result.iv = NULL;
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        return result;
    }
    
    memcpy(result.key, aes_key_bytes, 32);
    
    // 清理临时缓冲区
    free(padded_data);
    
    return result;
}