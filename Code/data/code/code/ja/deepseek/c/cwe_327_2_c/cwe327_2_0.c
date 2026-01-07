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
    
    // アルゴリズムの選択: AES-256-CBCを選択（キーのプレフィックス32バイトを使用）
    const int ALGORITHM_KEY_LENGTH = 32; // AES-256用の32バイトキー
    const int IV_LENGTH = AES_BLOCK_SIZE; // AESのIV長は16バイト
    
    // キーの長さが十分か確認
    if (key_len < ALGORITHM_KEY_LENGTH) {
        return result; // キーが短すぎる
    }
    
    // キーを割り当ててコピー
    result.key = (unsigned char*)malloc(ALGORITHM_KEY_LENGTH);
    if (!result.key) {
        return result;
    }
    memcpy(result.key, key, ALGORITHM_KEY_LENGTH);
    
    // IVを割り当てて生成
    result.iv = (unsigned char*)malloc(IV_LENGTH);
    if (!result.iv) {
        free(result.key);
        result.key = NULL;
        return result;
    }
    
    if (RAND_bytes(result.iv, IV_LENGTH) != 1) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // 暗号化データ用のバッファを割り当て（パディング用に余分に）
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        result.key = NULL;
        result.iv = NULL;
        return result;
    }
    
    // AESコンテキストの設定
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, ALGORITHM_KEY_LENGTH * 8, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // データを暗号化
    unsigned char* temp_data = (unsigned char*)malloc(padded_len);
    if (!temp_data) {
        free(result.key);
        free(result.iv);
        free(result.encrypted_data);
        result.key = NULL;
        result.iv = NULL;
        result.encrypted_data = NULL;
        return result;
    }
    
    // 元のデータをコピー
    memcpy(temp_data, data, data_len);
    
    // PKCS#7パディングを適用
    unsigned char pad_value = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = data_len; i < padded_len; i++) {
        temp_data[i] = pad_value;
    }
    
    // CBCモードでAES暗号化を実行
    unsigned char ivec[IV_LENGTH];
    memcpy(ivec, result.iv, IV_LENGTH);
    
    AES_cbc_encrypt(temp_data, result.encrypted_data, padded_len, &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = padded_len;
    
    // 一時バッファを解放
    free(temp_data);
    
    return result;
}