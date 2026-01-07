#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <memory>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>

std::string create_private_key() {
    const int key_length = 2048;
    std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> pkey(nullptr, EVP_PKEY_free);
    std::unique_ptr<EVP_PKEY_CTX, decltype(&EVP_PKEY_CTX_free)> ctx(nullptr, EVP_PKEY_CTX_free);
    std::unique_ptr<BIO, decltype(&BIO_free)> bio(nullptr, BIO_free);
    
    // 키 생성 컨텍스트 생성
    ctx.reset(EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr));
    if (!ctx) {
        throw std::runtime_error("Failed to create PKEY context");
    }
    
    // 키 초기화
    if (EVP_PKEY_keygen_init(ctx.get()) <= 0) {
        throw std::runtime_error("Failed to initialize key generation");
    }
    
    // RSA 키 길이 설정
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx.get(), key_length) <= 0) {
        throw std::runtime_error("Failed to set RSA key length");
    }
    
    // 키 생성
    EVP_PKEY* raw_pkey = nullptr;
    if (EVP_PKEY_keygen(ctx.get(), &raw_pkey) <= 0) {
        throw std::runtime_error("Failed to generate RSA key");
    }
    pkey.reset(raw_pkey);
    
    // 메모리 BIO 생성
    bio.reset(BIO_new(BIO_s_mem()));
    if (!bio) {
        throw std::runtime_error("Failed to create BIO");
    }
    
    // PEM 형식으로 개인 키 내보내기
    if (PEM_write_bio_PrivateKey(bio.get(), pkey.get(), nullptr, nullptr, 0, nullptr, nullptr) <= 0) {
        throw std::runtime_error("Failed to write private key to BIO");
    }
    
    // BIO에서 문자열 추출
    BUF_MEM* buf_mem = nullptr;
    BIO_get_mem_ptr(bio.get(), &buf_mem);
    if (!buf_mem || !buf_mem->data || buf_mem->length == 0) {
        throw std::runtime_error("Failed to get private key data from BIO");
    }
    
    return std::string(buf_mem->data, buf_mem->length);
}