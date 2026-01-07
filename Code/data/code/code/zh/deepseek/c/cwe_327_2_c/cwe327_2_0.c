#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // 选择AES-256-CBC算法（使用密钥的前32字节）
    const int algorithm_key_len = 32; // AES-256需要32字节密钥
    const int iv_len = AES_BLOCK_SIZE; // AES的IV长度是16字节
    
    // 检查密钥长度是否足够
    if (key_len < algorithm_key_len) {
        return result; // 返回空结果
    }
    
    // 分配并复制密钥（使用前32字节）
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (!result.key) {
        return result;
    }
    memcpy(result.key, key, algorithm_key_len);
    
    // 分配并生成IV
    result.iv = (unsigned char*)malloc(iv_len);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 计算填充后的数据长度
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    
    // 分配加密数据缓冲区
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 创建AES密钥结构
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // 复制数据到临时缓冲区并添加PKCS#7填充
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    memcpy(padded_data, data, data_len);
    
    // 添加PKCS#7填充
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // 执行AES-CBC加密
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    
    // 设置加密数据长度
    result.encrypted_len = padded_len;
    
    // 清理临时缓冲区
    free(padded_data);
    
    return result;
}