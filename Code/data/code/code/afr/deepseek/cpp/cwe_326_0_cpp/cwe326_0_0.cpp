#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <memory>
#include <string>
#include <stdexcept>
#include <cstdio>
#include <cstring>

std::string create_private_key() {
    // OpenSSL 초기화
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // RSA 키 생성을 위한 EVP_PKEY 컨텍스트
    std::unique_ptr<EVP_PKEY_CTX, decltype(&EVP_PKEY_CTX_free)> ctx(
        EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr),
        EVP_PKEY_CTX_free
    );
    
    if (!ctx) {
        throw std::runtime_error("EVP_PKEY_CTX_new_id failed");
    }

    if (EVP_PKEY_keygen_init(ctx.get()) <= 0) {
        throw std::runtime_error("EVP_PKEY_keygen_init failed");
    }

    // RSA 키 길이 설정 (2048비트)
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx.get(), 2048) <= 0) {
        throw std::runtime_error("EVP_PKEY_CTX_set_rsa_keygen_bits failed");
    }

    // 키 생성
    EVP_PKEY* pkey = nullptr;
    if (EVP_PKEY_keygen(ctx.get(), &pkey) <= 0) {
        throw std::runtime_error("EVP_PKEY_keygen failed");
    }
    
    std::unique_ptr<EVP_PKEY, decltype(&EVP_PKEY_free)> key(pkey, EVP_PKEY_free);

    // 메모리 BIO를 사용하여 PEM 형식으로 내보내기
    std::unique_ptr<BIO, decltype(&BIO_free)> bio(
        BIO_new(BIO_s_mem()),
        BIO_free
    );
    
    if (!bio) {
        throw std::runtime_error("BIO_new failed");
    }

    // PEM 형식으로 개인 키 쓰기
    if (!PEM_write_bio_PrivateKey(bio.get(), key.get(), nullptr, nullptr, 0, nullptr, nullptr)) {
        throw std::runtime_error("PEM_write_bio_PrivateKey failed");
    }

    // BIO에서 문자열 추출
    char* data = nullptr;
    long len = BIO_get_mem_data(bio.get(), &data);
    
    if (len <= 0 || !data) {
        throw std::runtime_error("BIO_get_mem_data failed");
    }

    // 정리
    EVP_cleanup();
    ERR_free_strings();

    return std::string(data, len);
}