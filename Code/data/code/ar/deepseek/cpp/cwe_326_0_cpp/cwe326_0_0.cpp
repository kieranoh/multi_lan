#include <string>
#include <memory>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <cstdio>
#include <cstdlib>

std::string create_private_key() {
    // طول المفتاح المطلوب (يمكن تعديله حسب الحاجة)
    const int key_length = 2048;
    
    // تهيئة مكتبة OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // إنشاء سياق توليد المفتاح
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
    
    // تعيين خيار طول المفتاح
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, key_length) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    // توليد المفتاح
    EVP_PKEY* pkey = NULL;
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }
    
    // تنظيف سياق التوليد
    EVP_PKEY_CTX_free(ctx);
    
    // إنشاء BIO لكتابة المفتاح بتنسيق PEM
    BIO* bio = BIO_new(BIO_s_mem());
    if (!bio) {
        ERR_print_errors_fp(stderr);
        EVP_PKEY_free(pkey);
        return "";
    }
    
    // كتابة المفتاح الخاص بتنسيق PEM
    if (!PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, NULL, NULL)) {
        ERR_print_errors_fp(stderr);
        BIO_free(bio);
        EVP_PKEY_free(pkey);
        return "";
    }
    
    // قراءة البيانات من BIO إلى سلسلة
    BUF_MEM* bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string privateKeyPem(bufferPtr->data, bufferPtr->length);
    
    // تنظيف الموارد
    BIO_free(bio);
    EVP_PKEY_free(pkey);
    
    // تنظيف OpenSSL
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();
    
    return privateKeyPem;
}