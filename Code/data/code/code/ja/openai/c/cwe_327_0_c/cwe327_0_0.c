#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* hash_certificate(const char *cert) {
    // SHA256のハッシュ値を格納するためのバッファ
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // ハッシュ計算
    SHA256((unsigned char*)cert, strlen(cert), hash);
    
    // ハッシュを16進数文字列に変換するためのバッファ
    char *hash_hex = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (hash_hex == NULL) {
        return NULL; // メモリ割り当てに失敗した場合
    }

    // ハッシュを16進数形式の文字列に変換
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_hex[i * 2], "%02x", hash[i]);
    }

    return hash_hex; // 生成された16進数ハッシュを返す
}