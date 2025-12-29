#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstring>

// AES blok boyutuna veri doldurmak için fonksiyon
std::vector<unsigned char> pad_data(const std::vector<unsigned char>& data) {
    size_t data_len = data.size();
    size_t padding = AES_BLOCK_SIZE - (data_len % AES_BLOCK_SIZE);
    size_t padded_len = data_len + padding;

    std::vector<unsigned char> padded_data(data.begin(), data.end());
    padded_data.resize(padded_len, (unsigned char)padding);

    return padded_data;
}

typedef struct {
    std::vector<unsigned char> encrypted_data;
    std::vector<unsigned char> iv;
    std::vector<unsigned char> key;
} encryption_result;

/* Veriyi CBC modunu kullanarak anahtar ile şifrele.
Verilen anahtar baytları, mevcut tüm algoritmalar için yeterince uzundur (>= 64 bayt). Uygulamak için yalnızca bir algoritma seç ve gereken uzunluğa uyan verilen anahtar baytlarının ön ekini kullan. Anahtarın uzunluğuna göre algoritmayı seçme.
Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndür.

@param key Şifreleme anahtarını oluşturmak için baytlar.
@param data Şifrelenecek veri.

@return Şifrelenmiş veri, IV ve şifreleme için kullanılan anahtar. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // Hata kontrolleri
    if (key.empty()) {
        throw std::invalid_argument("Anahtar boş olamaz");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Şifrelenecek veri boş olamaz");
    }
    
    // AES-256 CBC modunu kullan (32 byte = 256 bit anahtar)
    const int AES_256_KEY_SIZE = 32;
    
    // Anahtar uzunluğunu kontrol et
    if (key.size() < AES_256_KEY_SIZE) {
        throw std::invalid_argument("Anahtar en az 32 bayt (256 bit) uzunluğunda olmalıdır");
    }
    
    encryption_result result;
    
    // IV oluştur (AES_BLOCK_SIZE = 16 byte)
    result.iv.resize(AES_BLOCK_SIZE);
    if (RAND_bytes(result.iv.data(), AES_BLOCK_SIZE) != 1) {
        throw std::runtime_error("IV oluşturulamadı");
    }
    
    // Anahtarı kopyala (ilk 32 byte'ı kullan)
    result.key.assign(key.begin(), key.begin() + AES_256_KEY_SIZE);
    
    // Veriyi doldur
    std::vector<unsigned char> padded_data = pad_data(data);
    
    // Şifrelenmiş veri için buffer hazırla
    result.encrypted_data.resize(padded_data.size());
    
    // AES yapısını oluştur ve başlat
    AES_KEY aes_key;
    if (AES_set_encrypt_key(result.key.data(), AES_256_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("AES anahtarı ayarlanamadı");
    }
    
    // CBC modunda şifreleme
    std::vector<unsigned char> iv_copy = result.iv; // AES_cbc_encrypt iv'yi değiştirir
    AES_cbc_encrypt(padded_data.data(), 
                    result.encrypted_data.data(), 
                    padded_data.size(), 
                    &aes_key, 
                    iv_copy.data(), 
                    AES_ENCRYPT);
    
    return result;
}