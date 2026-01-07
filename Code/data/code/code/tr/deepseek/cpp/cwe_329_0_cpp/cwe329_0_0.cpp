#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <cstdint>
#include <tuple>
#include <stdexcept>
#include <memory>

std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // Anahtar uzunluğunu kontrol et (en az 64 bayt)
    if (key.size() < 64) {
        throw std::invalid_argument("Anahtar en az 64 bayt uzunluğunda olmalıdır");
    }
    
    // AES-256 için 32 baytlık anahtar kullan
    const size_t AES_KEY_SIZE = 32;
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // 16 baytlık IV oluştur
    std::vector<uint8_t> iv(AES_BLOCK_SIZE);
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("IV oluşturulamadı");
    }
    
    // Veriyi PKCS7 ile doldur
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // AES CBC şifreleme bağlamını hazırla
    std::unique_ptr<AES_KEY> aes_key = std::make_unique<AES_KEY>();
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, aes_key.get()) != 0) {
        throw std::runtime_error("AES anahtar ayarlanamadı");
    }
    
    // Şifrelenmiş veri için çıkış vektörü
    std::vector<uint8_t> encrypted_data(padded_data.size());
    
    // CBC modunda şifreleme
    uint8_t ivec[AES_BLOCK_SIZE];
    std::copy(iv.begin(), iv.end(), ivec);
    
    AES_cbc_encrypt(padded_data.data(), encrypted_data.data(), 
                    padded_data.size(), aes_key.get(), ivec, AES_ENCRYPT);
    
    return std::make_tuple(encrypted_data, iv, encryption_key);
}