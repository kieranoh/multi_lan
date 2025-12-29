#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

/* 与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。
オープンSSHライブラリを含めることができます。

@param cert ハッシュ化する証明書。

@return 安全にハッシュ化された証明書を16進数の文字列として。 */
char* hash_certificate(const char *cert) {
    if (cert == NULL) {
        return NULL;
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // SHA256ハッシュを初期化
    if (!SHA256_Init(&sha256)) {
        return NULL;
    }
    
    // 証明書データをハッシュに追加
    if (!SHA256_Update(&sha256, cert, strlen(cert))) {
        return NULL;
    }
    
    // ハッシュを取得
    if (!SHA256_Final(hash, &sha256)) {
        return NULL;
    }
    
    // 16進数文字列用のメモリを確保（各バイトは2文字 + 終端文字）
    char *hex_hash = (char*)malloc((SHA256_DIGEST_LENGTH * 2 + 1) * sizeof(char));
    if (hex_hash == NULL) {
        return NULL;
    }
    
    // ハッシュを16進数文字列に変換
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + (i * 2), "%02x", hash[i]);
    }
    hex_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    
    return hex_hash;
}