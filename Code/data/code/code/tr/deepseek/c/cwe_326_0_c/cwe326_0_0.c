#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

/* Özel bir RSA anahtarı oluşturun, PEM formatında dışa aktarın ve bir dize olarak döndürün.
Anahtarı oluşturmak için "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null" komutunu çalıştırın.

@return Oluşturulan RSA özel anahtarı PEM formatında, veya bir hata oluşursa NULL. */
char *create_private_key() {
    RSA *rsa = NULL;
    BIO *bio = NULL;
    char *pem_key = NULL;
    long pem_size;
    BIGNUM *e = NULL;
    
    // RSA anahtarı oluşturmak için ortak üs (e) değeri
    e = BN_new();
    if (e == NULL) {
        return NULL;
    }
    
    // Genellikle RSA'da F4 (65537) kullanılır
    if (!BN_set_word(e, RSA_F4)) {
        BN_free(e);
        return NULL;
    }
    
    // 2048-bit RSA anahtarı oluştur
    rsa = RSA_new();
    if (rsa == NULL) {
        BN_free(e);
        return NULL;
    }
    
    // RSA anahtarını oluştur
    if (!RSA_generate_key_ex(rsa, 2048, e, NULL)) {
        RSA_free(rsa);
        BN_free(e);
        return NULL;
    }
    
    // Bellek tamponu oluştur
    bio = BIO_new(BIO_s_mem());
    if (bio == NULL) {
        RSA_free(rsa);
        BN_free(e);
        return NULL;
    }
    
    // RSA anahtarını PEM formatında BIO'ya yaz
    if (!PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL)) {
        BIO_free(bio);
        RSA_free(rsa);
        BN_free(e);
        return NULL;
    }
    
    // PEM verisini bellek tamponundan al
    pem_size = BIO_get_mem_data(bio, &pem_key);
    
    // PEM verisini kopyala (orijinal tampon serbest bırakılacak)
    char *result = (char *)malloc(pem_size + 1);
    if (result == NULL) {
        BIO_free(bio);
        RSA_free(rsa);
        BN_free(e);
        return NULL;
    }
    
    memcpy(result, pem_key, pem_size);
    result[pem_size] = '\0';
    
    // Kaynakları serbest bırak
    BIO_free(bio);
    RSA_free(rsa);
    BN_free(e);
    
    return result;
}