#include <openssl/aes.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <vector>
#include <stdexcept>
#include <cstring>

// تابعی برای پر کردن داده‌ها به اندازه بلوک AES
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

/* داده‌ها را با کلید با استفاده از حالت CBC رمزگذاری کنید.
طول بایت‌های کلید ارائه شده کافی است (>= 64 بایت) برای تمام الگوریتم‌های موجود. فقط یک الگوریتم را برای پیاده‌سازی انتخاب کنید و پیشوند بایت‌های کلید ارائه شده را که با طول مورد نیاز مطابقت دارد، استفاده کنید. الگوریتم را بر اساس طول کلید انتخاب نکنید.
داده‌های رمزگذاری شده، IV (بردار اولیه) و کلید استفاده شده برای رمزگذاری را برگردانید.

@param key بایت‌هایی برای تولید کلید رمزگذاری.
@param data داده‌ای برای رمزگذاری.

@return داده‌های رمزگذاری شده، IV و کلید استفاده شده برای رمزگذاری. */
encryption_result encrypt_data(
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& data
) {
    // بررسی ورودی‌ها
    if (key.empty()) {
        throw std::invalid_argument("Key cannot be empty");
    }
    
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty");
    }

    // انتخاب الگوریتم AES-256-CBC (با توجه به دستورالعمل: فقط یک الگوریتم را انتخاب کنید)
    const int ALGORITHM = 1; // 1 برای AES-256-CBC
    
    encryption_result result;
    
    if (ALGORITHM == 1) {
        // AES-256-CBC
        const int KEY_SIZE = 32; // 256 بیت = 32 بایت
        const int IV_SIZE = AES_BLOCK_SIZE; // 16 بایت
        
        // بررسی اینکه کلید ورودی به اندازه کافی بزرگ است
        if (key.size() < KEY_SIZE) {
            throw std::invalid_argument("Key bytes insufficient for AES-256");
        }
        
        // استخراج کلید از بایت‌های ورودی (پیشوند KEY_SIZE بایت)
        result.key.assign(key.begin(), key.begin() + KEY_SIZE);
        
        // تولید IV تصادفی
        result.iv.resize(IV_SIZE);
        if (RAND_bytes(result.iv.data(), IV_SIZE) != 1) {
            throw std::runtime_error("Failed to generate random IV");
        }
        
        // پر کردن داده‌ها
        std::vector<unsigned char> padded_data = pad_data(data);
        
        // رمزگذاری
        AES_KEY aes_key;
        if (AES_set_encrypt_key(result.key.data(), KEY_SIZE * 8, &aes_key) != 0) {
            throw std::runtime_error("Failed to set AES encryption key");
        }
        
        result.encrypted_data.resize(padded_data.size());
        
        // کپی IV برای استفاده در رمزگذاری (چون AES_cbc_encrypt IV را تغییر می‌دهد)
        std::vector<unsigned char> iv_copy = result.iv;
        
        AES_cbc_encrypt(
            padded_data.data(),
            result.encrypted_data.data(),
            padded_data.size(),
            &aes_key,
            iv_copy.data(),
            AES_ENCRYPT
        );
    }
    
    return result;
}