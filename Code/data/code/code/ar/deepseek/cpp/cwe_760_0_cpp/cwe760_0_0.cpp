#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstring>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // التحقق من صحة المدخلات
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("عدد كلمات المرور أكبر من حجم المصفوفات المقدمة");
    }
    
    // تهيئة المتجه الناتج
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    // حجم ناتج التجزئة لـ SHA-256 هو 32 بايت
    const int hash_length = 32;
    const int iterations = 10000;
    
    for (int i = 0; i < count; ++i) {
        // إنشاء ملح عشوائي بنفس طول ناتج التجزئة (32 بايت)
        std::vector<unsigned char> salt(hash_length);
        
        // في بيئة إنتاج حقيقية، يجب استخدام مولد أرقام عشوائية آمن مشفر
        // هنا نستخدم RAND_bytes من OpenSSL
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("فشل في توليد الملح العشوائي");
        }
        
        // تجهيز كلمة المرور المشفرة
        std::vector<unsigned char> hashed_password(hash_length);
        
        // استخدام PKCS5_PBKDF2_HMAC لتشفير كلمة المرور
        int ret = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // كلمة المرور
            passwords[i].length(),         // طول كلمة المرور
            salt.data(),                   // الملح
            salt.size(),                   // طول الملح
            iterations,                    // عدد التكرارات
            EVP_sha256(),                  // دالة التجزئة
            hash_length,                   // طول الناتج المطلوب
            hashed_password.data()         // مؤشر إلى ناتج التجزئة
        );
        
        if (ret != 1) {
            throw std::runtime_error("فشل في تشفير كلمة المرور");
        }
        
        // إضافة النتيجة إلى المتجه الناتج
        result.emplace_back(std::move(hashed_password), std::move(salt));
    }
    
    return result;
}