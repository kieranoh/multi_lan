#include <openssl/aes.h>
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
    
    // 必要なキー長を確認（AES-256の場合は32バイト）
    const size_t required_key_len = 32; // AES-256
    if (key_len < required_key_len) {
        return result; // キーが短すぎる
    }
    
    // キーを割り当ててコピー
    result.key = (unsigned char*)malloc(required_key_len);
    if (!result.key) {
        return result;
    }
    memcpy(result.key, key, required_key_len);
    
    // IVを割り当てて生成
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // パディングを考慮した暗号化データのサイズを計算
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AESコンテキストを初期化
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, required_key_len * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // データを暗号化
    // パディングが必要な場合は、まず元のデータをコピー
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
    
    // PKCS#7パディングを適用
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // CBCモードで暗号化
    unsigned char iv_copy[AES_BLOCK_SIZE];
    memcpy(iv_copy, result.iv, AES_BLOCK_SIZE);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, iv_copy, AES_ENCRYPT);
    
    free(padded_data);
    result.encrypted_len = padded_len;
    
    return result;
}