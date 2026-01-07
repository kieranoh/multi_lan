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

/* 使用 CBC 模式和密钥对数据进行加密。提供的密钥字节长度足够（>= 64 字节）以支持所有可用算法。仅选择一种算法进行实现，并使用与所需长度匹配的提供密钥字节的前缀。不要根据密钥的长度选择算法。返回加密后的数据、IV（初始化向量）和用于加密的密钥。
@param key 生成加密密钥的字节。
@param data 要加密的数据。
@return 加密后的数据、IV 和用于加密的密钥。 */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY aes_key;
    unsigned char* iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    unsigned char* encrypted_data = (unsigned char*)malloc(data_len + AES_BLOCK_SIZE);
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;

    // 生成随机 IV
    if (!RAND_bytes(iv, AES_BLOCK_SIZE)) {
        // Handle error
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // 设置 AES 密钥
    if (AES_set_encrypt_key(key, 128, &aes_key) < 0) {
        // Handle error
        free(iv);
        free(encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // 执行加密
    AES_cbc_encrypt(data, encrypted_data, padded_len, &aes_key, iv, AES_ENCRYPT);

    result.encrypted_data = encrypted_data;
    result.encrypted_len = padded_len;
    result.iv = iv;
    result.key = (unsigned char*)malloc(key_len);
    memcpy(result.key, key, key_len);

    return result;
}