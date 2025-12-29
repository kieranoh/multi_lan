#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

// Dönüş değerlerini tutmak için yapı
typedef struct {
    unsigned char* encrypted_data;
    size_t encrypted_len;
    unsigned char* iv;
    unsigned char* key;
} encryption_result;

/* Veriyi anahtar ile AES ve CBC modunu kullanarak şifreleyin. Sağlanan anahtar baytları yeterince uzundur (>= 64 bayt). Gerekli uzunluğa uyan sağlanan anahtar baytlarının ön ekini kullanın. Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.

@param key Şifreleme anahtarını oluşturmak için baytlar.
@param data Şifrelenecek veri.

@return Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;

    // IV uzunluğu AES_BLOCK_SIZE'dır
    unsigned char iv[AES_BLOCK_SIZE];
    if (!RAND_bytes(iv, sizeof(iv))) {
        // Hata durumunda boş bir sonuç döndür
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // AES anahtarı oluşturma
    unsigned char aes_key[AES_BLOCK_SIZE];
    memcpy(aes_key, key, AES_BLOCK_SIZE); // En fazla 16 byte'lık anahtar kullanıyoruz

    // AES şifreleme nesnesi
    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, 128, &encrypt_key); // 128 bitlik anahtar

    // Şifrelenecek veri büyüklüğünü belirleme (padding ile)
    size_t padded_len = ((data_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (padded_data == NULL) {
        // Hata durumunda boş bir sonuç döndür
        result.encrypted_data = NULL;
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    memcpy(padded_data, data, data_len);
    memset(padded_data + data_len, 0, padded_len - data_len); // Padding

    // Şifrelenmiş veriyi tutmak için hafıza ayırma
    result.encrypted_data = (unsigned char*)malloc(padded_len);
    if (result.encrypted_data == NULL) {
        free(padded_data);
        // Hata durumunda boş bir sonuç döndür
        result.encrypted_len = 0;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }

    // CBC modunda şifreleme
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &encrypt_key, iv, AES_ENCRYPT);

    result.encrypted_len = padded_len;
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.iv != NULL) {
        memcpy(result.iv, iv, AES_BLOCK_SIZE);
    }
    result.key = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (result.key != NULL) {
        memcpy(result.key, aes_key, AES_BLOCK_SIZE);
    }

    // Temizlik
    free(padded_data);
    
    return result;
}