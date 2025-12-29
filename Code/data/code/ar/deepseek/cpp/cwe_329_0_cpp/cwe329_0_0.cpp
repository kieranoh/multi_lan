#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <cstring>
#include <stdexcept>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // التحقق من أن المفتاح طويل بما يكفي (64 بايت على الأقل كما هو مطلوب)
    if (key.size() < 64) {
        throw std::invalid_argument("يجب أن يكون المفتاح بطول 64 بايت على الأقل");
    }
    
    // استخدام أول 32 بايت من المفتاح كمفتاح AES-256 (256 بت = 32 بايت)
    const size_t AES_KEY_SIZE = 32;
    std::vector<uint8_t> aes_key(key.begin(), key.begin() + AES_KEY_SIZE);
    
    // توليد IV عشوائي (16 بايت لـ AES)
    const size_t IV_SIZE = 16;
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("فشل في توليد IV عشوائي");
    }
    
    // تعبئة البيانات وفقًا لـ PKCS7
    const size_t AES_BLOCK_SIZE = 16;
    std::vector<uint8_t> padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);
    
    // إعداد سياق AES
    AES_KEY aes_ctx;
    if (AES_set_encrypt_key(aes_key.data(), AES_KEY_SIZE * 8, &aes_ctx) != 0) {
        throw std::runtime_error("فشل في إعداد مفتاح التشفير");
    }
    
    // تشفير البيانات باستخدام وضع CBC
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> current_iv = iv; // نسخة من IV للتعديل
    
    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR مع IV أو الكتلة المشفرة السابقة
        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            padded_data[i + j] ^= current_iv[j];
        }
        
        // تشفير الكتلة
        AES_encrypt(&padded_data[i], &encrypted_data[i], &aes_ctx);
        
        // تحديث IV للكتلة التالية
        memcpy(current_iv.data(), &encrypted_data[i], AES_BLOCK_SIZE);
    }
    
    return std::make_tuple(encrypted_data, iv, aes_key);
}

// دالة مساعدة لتعبئة البيانات وفقًا لـ PKCS7
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}