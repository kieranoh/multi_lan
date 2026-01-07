#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <memory>
#include <string>
#include <cstdio>
#include <cstdlib>

std::string create_private_key() {
    // RSA 키 생성 파라미터 설정
    const int KEY_LENGTH = 2048;
    const unsigned long RSA_F4 = 65537;
    
    // RSA 키 생성
    std::unique_ptr<RSA, decltype(&RSA_free)> rsa(RSA_new(), RSA_free);
    std::unique_ptr<BIGNUM, decltype(&BN_free)> bn(BN_new(), BN_free);
    
    if (!rsa || !bn) {
        return nullptr;
    }
    
    // 공개 지수 설정 (일반적으로 65537 사용)
    if (BN_set_word(bn.get(), RSA_F4) != 1) {
        return nullptr;
    }
    
    // RSA 키 생성
    if (RSA_generate_key_ex(rsa.get(), KEY_LENGTH, bn.get(), nullptr) != 1) {
        return nullptr;
    }
    
    // 메모리 BIO 생성 (파일 없이 메모리에서 작업)
    std::unique_ptr<BIO, decltype(&BIO_free_all)> bio(BIO_new(BIO_s_mem()), BIO_free_all);
    if (!bio) {
        return nullptr;
    }
    
    // PEM 형식으로 RSA 개인 키 쓰기
    if (PEM_write_bio_RSAPrivateKey(bio.get(), rsa.get(), nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        return nullptr;
    }
    
    // BIO에서 데이터 읽기
    BUF_MEM *bufferPtr;
    BIO_get_mem_ptr(bio.get(), &bufferPtr);
    
    if (!bufferPtr || bufferPtr->length == 0) {
        return nullptr;
    }
    
    // 문자열로 변환하여 반환
    return std::string(bufferPtr->data, bufferPtr->length);
}