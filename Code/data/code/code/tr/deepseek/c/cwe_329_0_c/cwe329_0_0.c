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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // Anahtar uzunluğunu kontrol et (en az 64 bayt)
    if (key_len < 64) {
        return result;
    }
    
    // AES-256 için 32 bayt anahtar ve 16 bayt IV kullan
    const int AES_KEY_LENGTH = 32; // 256 bit
    const int AES_IV_LENGTH = 16;  // 128 bit
    
    // Anahtar ve IV için bellek ayır
    result.key = (unsigned char*)malloc(AES_KEY_LENGTH);
    result.iv = (unsigned char*)malloc(AES_IV_LENGTH);
    
    if (!result.key || !result.iv) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Anahtarın ilk 32 baytını kullan
    memcpy(result.key, key, AES_KEY_LENGTH);
    
    // Rastgele IV oluştur
    if (RAND_bytes(result.iv, AES_IV_LENGTH) != 1) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // CBC modunda şifreleme için padding eklenir
    // PKCS#7 padding: en fazla 16 bayt eklenebilir
    size_t padded_len = data_len + AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    
    if (!padded_data) {
        free(result.key);
        free(result.iv);
        return result;
    }
    
    // Veriyi kopyala
    memcpy(padded_data, data, data_len);
    
    // PKCS#7 padding ekle
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    for (size_t i = 0; i < padding; i++) {
        padded_data[data_len + i] = (unsigned char)padding;
    }
    
    size_t final_len = data_len + padding;
    
    // Şifrelenmiş veri için bellek ayır
    result.encrypted_data = (unsigned char*)malloc(final_len);
    if (!result.encrypted_data) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        return result;
    }
    
    // AES yapısını başlat
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, 256, &aes_key) != 0) {
        free(result.key);
        free(result.iv);
        free(padded_data);
        free(result.encrypted_data);
        result.encrypted_data = NULL;
        return result;
    }
    
    // CBC modunda şifrele
    unsigned char ivec[AES_IV_LENGTH];
    memcpy(ivec, result.iv, AES_IV_LENGTH);
    
    AES_cbc_encrypt(padded_data, result.encrypted_data, final_len, &aes_key, ivec, AES_ENCRYPT);
    
    result.encrypted_len = final_len;
    
    // Geçici buffer'ı temizle
    free(padded_data);
    
    return result;
}