#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <stdlib.h>
#include <string.h>

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
    encryption_result result = {NULL, 0, NULL, NULL};
    
    // AES-256-CBC kullanacağız (gereken anahtar uzunluğu: 32 bayt)
    const int algorithm_key_len = 32; // AES-256 için
    const int iv_len = AES_BLOCK_SIZE; // AES için IV uzunluğu
    
    // Anahtar uzunluğu kontrolü
    if (key_len < algorithm_key_len) {
        // Yeterli anahtar uzunluğu yoksa boş sonuç döndür
        return result;
    }
    
    // IV için bellek ayır
    result.iv = (unsigned char*)malloc(iv_len);
    if (!result.iv) {
        return result;
    }
    
    // Rastgele IV oluştur
    if (RAND_bytes(result.iv, iv_len) != 1) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    
    // Anahtar için bellek ayır ve kopyala
    result.key = (unsigned char*)malloc(algorithm_key_len);
    if (!result.key) {
        free(result.iv);
        result.iv = NULL;
        return result;
    }
    memcpy(result.key, key, algorithm_key_len);
    
    // CBC modunda şifreleme için padding gerekecek
    // Maksimum şifrelenmiş veri uzunluğu: data_len + AES_BLOCK_SIZE (padding için)
    size_t max_encrypted_len = data_len + AES_BLOCK_SIZE;
    result.encrypted_data = (unsigned char*)malloc(max_encrypted_len);
    if (!result.encrypted_data) {
        free(result.iv);
        free(result.key);
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // AES şifreleme bağlamı oluştur
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key, algorithm_key_len * 8, &aes_key) != 0) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // CBC modunda şifreleme
    // OpenSSL'in AES_cbc_encrypt fonksiyonu padding uygulamaz, bu yüzden manuel padding yapmalıyız
    size_t padded_len = ((data_len + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char* padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        free(result.encrypted_data);
        free(result.iv);
        free(result.key);
        result.encrypted_data = NULL;
        result.iv = NULL;
        result.key = NULL;
        return result;
    }
    
    // Veriyi kopyala ve PKCS#7 padding uygula
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = padded_len - data_len;
    for (size_t i = data_len; i < padded_len; i++) {
        padded_data[i] = pad_value;
    }
    
    // Şifreleme işlemi
    AES_cbc_encrypt(padded_data, result.encrypted_data, padded_len, &aes_key, result.iv, AES_ENCRYPT);
    result.encrypted_len = padded_len;
    
    // Geçici buffer'ı temizle
    free(padded_data);
    
    return result;
}