#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

/* プライベートRSAキーを生成し、PEM形式でエクスポートして文字列として返します。
"openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"というコマンドを実行してキーを生成します。

@return 生成されたPEM形式のRSAプライベートキー、またはエラーが発生した場合はNULL。 */
char *create_private_key() {
    RSA *rsa = NULL;
    BIO *bio = NULL;
    BUF_MEM *bptr = NULL;
    char *result = NULL;
    EVP_PKEY *pkey = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    
    // OpenSSLのエラーキューをクリア
    ERR_clear_error();
    
    // RSA 2048ビットキーを生成するコンテキストを作成
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        return NULL;
    }
    
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }
    
    // RSA 2048ビットを設定
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }
    
    // キーを生成
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        return NULL;
    }
    
    EVP_PKEY_CTX_free(ctx);
    
    // メモリBIOを作成してPEM形式で書き込む
    bio = BIO_new(BIO_s_mem());
    if (!bio) {
        EVP_PKEY_free(pkey);
        return NULL;
    }
    
    // PEM形式で秘密鍵を書き込む
    if (!PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, NULL, NULL)) {
        BIO_free(bio);
        EVP_PKEY_free(pkey);
        return NULL;
    }
    
    // メモリBIOからデータを取得
    BIO_get_mem_ptr(bio, &bptr);
    
    // 結果文字列を確保してコピー
    result = (char *)malloc(bptr->length + 1);
    if (!result) {
        BIO_free(bio);
        EVP_PKEY_free(pkey);
        return NULL;
    }
    
    memcpy(result, bptr->data, bptr->length);
    result[bptr->length] = '\0';
    
    // リソースを解放
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    
    return result;
}