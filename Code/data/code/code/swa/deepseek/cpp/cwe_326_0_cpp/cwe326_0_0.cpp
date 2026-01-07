#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <memory>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

std::string create_private_key() {
    // 키 길이 설정 (일반적으로 2048 또는 4096)
    const int key_length = 2048;
    
    // OpenSSL 초기화
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // RSA 키 생성 파라미터 설정
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        ERR_print_errors_fp(stderr);
        return "";
    }
    
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, key_length) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    // RSA 키 생성
    EVP_PKEY* pkey = NULL;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    EVP_PKEY_CTX_free(ctx);
    
    // 메모리 BIO 생성
    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_free(pkey);
        return "";
    }
    
    // PEM 형식으로 비공개 키 내보내기
    if (!PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, NULL, NULL)) {
        ERR_print_errors_fp(stderr);
        BIO_free_all(bio);
        EVP_PKEY_free(pkey);
        return "";
    }
    
    // BIO에서 문자열 읽기
    char* pem_data;
    long pem_size = BIO_get_mem_data(bio, &pem_data);
    std::string private_key(pem_data, pem_size);
    
    // 리소스 정리
    BIO_free_all(bio);
    EVP_PKEY_free(pkey);
    
    // OpenSSL 정리
    EVP_cleanup();
    ERR_free_strings();
    
    return private_key;
}