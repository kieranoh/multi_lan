#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

char *create_private_key() {
    RSA *rsa = NULL;
    BIO *bio = NULL;
    char *pem_key = NULL;
    long pem_size;
    
    // تهيئة OpenSSL
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    
    // إنشاء مفتاح RSA
    rsa = RSA_new();
    if (rsa == NULL) {
        fprintf(stderr, "خطأ في إنشاء كائن RSA\n");
        return NULL;
    }
    
    // إنشاء مفتاح RSA بحجم 2048 بت (يمكن تغييره حسب الحاجة)
    BIGNUM *bn = BN_new();
    if (bn == NULL) {
        fprintf(stderr, "خطأ في إنشاء BIGNUM\n");
        RSA_free(rsa);
        return NULL;
    }
    
    BN_set_word(bn, RSA_F4); // استخدام الأس العام 65537
    
    if (RSA_generate_key_ex(rsa, 2048, bn, NULL) != 1) {
        fprintf(stderr, "خطأ في إنشاء مفتاح RSA\n");
        ERR_print_errors_fp(stderr);
        BN_free(bn);
        RSA_free(rsa);
        return NULL;
    }
    
    BN_free(bn);
    
    // إنشاء BIO للكتابة في الذاكرة
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        fprintf(stderr, "خطأ في إنشاء BIO\n");
        RSA_free(rsa);
        return NULL;
    }
    
    // كتابة المفتاح الخاص بتنسيق PEM إلى BIO
    if (PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL) != 1) {
        fprintf(stderr, "خطأ في كتابة المفتاح الخاص بتنسيق PEM\n");
        ERR_print_errors_fp(stderr);
        BIO_free(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    // الحصول على حجم البيانات في BIO
    pem_size = BIO_get_mem_data(bio, NULL);
    if (pem_size <= 0) {
        fprintf(stderr, "خطأ في الحصول على حجم المفتاح PEM\n");
        BIO_free(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    // تخصيص ذاكرة للسلسلة
    pem_key = (char *)malloc(pem_size + 1);
    if (pem_key == NULL) {
        fprintf(stderr, "خطأ في تخصيص الذاكرة\n");
        BIO_free(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    // قراءة البيانات من BIO إلى السلسلة
    if (BIO_read(bio, pem_key, pem_size) != pem_size) {
        fprintf(stderr, "خطأ في قراءة المفتاح PEM\n");
        free(pem_key);
        BIO_free(bio);
        RSA_free(rsa);
        return NULL;
    }
    
    pem_key[pem_size] = '\0'; // إنهاء السلسلة
    
    // تنظيف الموارد
    BIO_free(bio);
    RSA_free(rsa);
    
    // تنظيف OpenSSL
    ERR_free_strings();
    EVP_cleanup();
    
    return pem_key;
}