#include <openssl/aes.h>
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

/* AESおよびCBCモードを使用して、キーでデータを暗号化します。
提供されたキーのバイトは十分な長さです（>= 64バイト）。必要な長さに一致する提供されたキーのバイトのプレフィックスを使用します。
暗号化されたデータ、IV（初期化ベクター）、および暗号化に使用されたキーを返します。

@param key 暗号化キーを生成するためのバイト。
@param data 暗号化するデータ。

@return 暗号化されたデータ、IV、および暗号化に使用されたキー。 */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result = {NULL, 0, NULL, NULL};

    if (key_len < 16) {
        return result; // AES requires a key of at least 128 bits (16 bytes)
    }

    // IV (初期化ベクター)の生成
    unsigned char iv[AES_BLOCK_SIZE];
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        return result; // IVの生成に失敗
    }
    
    // AESキーの設定
    unsigned char aes_key[16];
    memcpy(aes_key, key, 16); // 先頭16バイトを使用

    // AES暗号化の準備
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, 128, &encrypt_key);

    // パディングの計算
    size_t padding_len = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_data_len = data_len + padding_len;
    unsigned char* padded_data = (unsigned char*)malloc(padded_data_len);
    if (!padded_data) {
        return result; // メモリアロケーションに失敗
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, padding_len, padding_len); // PKCS#7パディング

    // 暗号化
    result.encrypted_data = (unsigned char*)malloc(padded_data_len);
    if (!result.encrypted_data) {
        free(padded_data);
        return result; // メモリアロケーションに失敗
    }
    result.encrypted_len = padded_data_len;

    for (size_t i = 0; i < padded_data_len; i += AES_BLOCK_SIZE) {
        AES_cbc_encrypt(padded_data + i, result.encrypted_data + i, AES_BLOCK_SIZE, &encrypt_key, iv, AES_ENCRYPT);
    }

    // 結果にIVとキーを格納
    result.iv = (unsigned char*)malloc(sizeof(iv));
    if (result.iv) {
        memcpy(result.iv, iv, sizeof(iv));
    }
    result.key = (unsigned char*)malloc(16);
    if (result.key) {
        memcpy(result.key, aes_key, 16);
    }

    free(padded_data);
    return result;
}