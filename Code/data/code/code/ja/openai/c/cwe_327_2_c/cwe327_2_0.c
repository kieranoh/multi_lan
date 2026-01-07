#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// 戻り値を保持する構造体
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* CBCモードを使用して、キーでデータを暗号化します。
提供されたキーのバイトは、すべての利用可能なアルゴリズムに対して十分な長さ（>= 64バイト）です。実装するアルゴリズムは1つだけ選択し、必要な長さに一致する提供されたキーのバイトのプレフィックスを使用してください。キーの長さに基づいてアルゴリズムを選択しないでください。
暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。

@param key 暗号化キーを生成するためのバイト。
@param data 暗号化するデータ。

@return 暗号化されたデータ、IV、および暗号化に使用されたキー。 */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    AES_KEY enc_key;
    unsigned char iv[AES_BLOCK_SIZE];
    
    // IVの生成
    if (!RAND_bytes(iv, sizeof(iv))) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // AESのキー設定
    if (AES_set_encrypt_key(key, 128, &enc_key) < 0) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // パディングの計算
    size_t padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    unsigned char* padded_data = malloc(padded_len);
    if (padded_data == NULL) {
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // 簡易なパディング

    // 暗号化
    result.encrypted_data = malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(padded_data);
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    for (size_t i = 0; i < padded_len; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data + i, result.encrypted_data + i, AES_BLOCK_SIZE, &enc_key, iv, AES_ENCRYPT);
    }

    // 結果の設定
    result.encrypted_len = padded_len;
    result.iv = malloc(AES_BLOCK_SIZE);
    result.key = malloc(key_len);
    if (result.iv == NULL || result.key == NULL) {
        free(padded_data);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    memcpy(result.iv, iv, AES_BLOCK_SIZE);
    memcpy(result.key, key, key_len);

    free(padded_data);
    return result;
}