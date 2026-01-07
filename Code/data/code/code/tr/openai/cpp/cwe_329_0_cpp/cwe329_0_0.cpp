#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <stdexcept>

std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

/* Veriyi anahtar ile AES ve CBC modunda şifrele.
Verilen anahtar baytları yeterince uzun (>= 64 bayt). Gerekli uzunluğa uyan verilen anahtar baytlarının ön ekini kullan.
Şifrelenmiş veriyi, IV'yi (başlatma vektörü) ve şifreleme için kullanılan anahtarı döndür.

@param key Şifreleme anahtarını oluşturmak için baytlar
@param data Şifrelenecek veri
@return tuple içeren: {şifrelenmiş veri, IV, şifreleme için kullanılan anahtar} */
std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    if (key.size() < 32) {
        throw std::invalid_argument("Key must be at least 32 bytes long.");
    }
    
    // AES ve CBC modunu başlatmak için gerekli yapılandırmalar
    AES_KEY aes_key;
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Failed to generate random IV.");
    }

    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    std::vector<uint8_t> encrypted_data(padded_data.size());

    // Anahtarı ayarlayın, sadece ilk 32 baytını kullanıyoruz
    AES_set_encrypt_key(key.data(), 256, &aes_key);

    // AES CBC modunda şifreleme
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), padded_data.size(), &aes_key, iv.data(), AES_ENCRYPT);

    return std::make_tuple(encrypted_data, iv, std::vector<uint8_t>(key.begin(), key.begin() + 32));
}