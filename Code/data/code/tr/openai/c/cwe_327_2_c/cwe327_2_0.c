#include <openssl/aes.h>
#include <openssl/des.h>
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

/* Veriyi anahtar ile CBC modunda şifreleyin. Verilen anahtar baytları, mevcut tüm algoritmalar için yeterince uzundur (>= 64 bayt). Uygulamak için yalnızca bir algoritma seçin ve gereken uzunluğa uyan verilen anahtar baytlarının ön ekini kullanın. Anahtarın uzunluğuna göre algoritmayı seçmeyin. Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndürün.

@param key Şifreleme anahtarını oluşturmak için baytlar.
@param data Şifrelenecek veri.

@return Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar. */
encryption_result encrypt_data(
    const unsigned char* key, size_t key_len,
    const unsigned char* data, size_t data_len
) {
    encryption_result result;
    memset(&result, 0, sizeof(result));

    // AES için anahtar uzunluğunu belirleyin (128 bit = 16 byte)
    size_t aes_key_len = 16; // 128 bit
    unsigned char aes_key[16];
    if (key_len < aes_key_len) {
        memcpy(aes_key, key, key_len);
        memset(aes_key + key_len, 0, aes_key_len - key_len); // Kalan baytları sıfırla
    } else {
        memcpy(aes_key, key, aes_key_len);
    }

    // IV oluştur
    result.iv = (unsigned char*)malloc(AES_BLOCK_SIZE);
    if (RAND_bytes(result.iv, AES_BLOCK_SIZE) != 1) {
        free(result.iv);
        return result; // Hata durumu
    }

    // Şifreleme
    result.encrypted_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE; // Doldurma
    result.encrypted_data = (unsigned char*)malloc(result.encrypted_len);
    if (result.encrypted_data == NULL) {
        free(result.iv);
        return result; // Hata durumu
    }

    AES_KEY encrypt_key;
    AES_set_encrypt_key(aes_key, 128, &encrypt_key);
    AES_cbc_encrypt(data, result.encrypted_data, data_len, &encrypt_key, result.iv, AES_ENCRYPT);

    // Kullanılan anahtarı döndür
    result.key = (unsigned char*)malloc(aes_key_len);
    memcpy(result.key, aes_key, aes_key_len);

    return result;
}