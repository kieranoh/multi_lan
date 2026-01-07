#include <openssl/aes.h>
#include <openssl/rand.h>
#include <vector>
#include <tuple>
#include <cstdint>
#include <cstring>
#include <stdexcept>

std::tuple<std::vector<uint8_t>, std::vector<uint8_t>, std::vector<uint8_t>>
encrypt_data(const std::vector<uint8_t>& key, const std::vector<uint8_t>& data) {
    // بررسی اندازه کلید
    if (key.size() < 64) {
        throw std::invalid_argument("Key must be at least 64 bytes");
    }

    // تعریف اندازه‌های مورد نیاز
    const size_t AES_KEY_SIZE = 32; // 256 بیت
    const size_t AES_BLOCK_SIZE = 16; // 128 بیت برای AES
    const size_t IV_SIZE = AES_BLOCK_SIZE;

    // استخراج کلید از 32 بایت اول ورودی کلید
    std::vector<uint8_t> encryption_key(key.begin(), key.begin() + AES_KEY_SIZE);

    // تولید IV تصادفی
    std::vector<uint8_t> iv(IV_SIZE);
    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
        throw std::runtime_error("Failed to generate random IV");
    }

    // پر کردن داده‌ها با PKCS7
    auto padded_data = pkcs7_pad(data, AES_BLOCK_SIZE);

    // ایجاد context برای AES
    AES_KEY aes_key;
    if (AES_set_encrypt_key(encryption_key.data(), AES_KEY_SIZE * 8, &aes_key) != 0) {
        throw std::runtime_error("Failed to set AES encryption key");
    }

    // رمزگذاری داده‌ها در حالت CBC
    std::vector<uint8_t> encrypted_data(padded_data.size());
    std::vector<uint8_t> prev_block = iv;

    for (size_t i = 0; i < padded_data.size(); i += AES_BLOCK_SIZE) {
        // XOR با بلوک قبلی (یا IV برای اولین بلوک)
        std::vector<uint8_t> xored_block(AES_BLOCK_SIZE);
        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            xored_block[j] = padded_data[i + j] ^ prev_block[j];
        }

        // رمزگذاری بلوک
        AES_encrypt(xored_block.data(), encrypted_data.data() + i, &aes_key);

        // به‌روزرسانی بلوک قبلی برای تکرار بعدی
        prev_block.assign(encrypted_data.begin() + i, encrypted_data.begin() + i + AES_BLOCK_SIZE);
    }

    return {encrypted_data, iv, encryption_key};
}

// تابع کمکی PKCS7 (همانطور که در سوال ارائه شده)
std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t block_size) {
    size_t padding_len = block_size - (data.size() % block_size);
    std::vector<uint8_t> padded = data;
    padded.insert(padded.end(), padding_len, static_cast<uint8_t>(padding_len));
    return padded;
}