#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

/**
 * @brief یک کلید خصوصی RSA تولید می‌کند، آن را با فرمت PEM صادر می‌کند و به عنوان یک رشته بازگردانید.
 * 
 * این تابع از دستور openssl برای تولید کلید خصوصی RSA با طول 2048 بیت استفاده می‌کند.
 * 
 * @return کلید خصوصی RSA تولید شده به فرمت PEM، یا یک رشته خالی اگر خطایی رخ داد.
 */
std::string create_private_key() {
    // طول کلید RSA (می‌تواند به عنوان پارامتر تابع نیز تعریف شود)
    const int key_length = 2048;
    
    // ساخت دستور openssl با طول کلید مشخص شده
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // باز کردن یک pipe برای خواندن خروجی دستور
    std::array<char, 128> buffer;
    std::string result;
    
    // استفاده از unique_ptr برای مدیریت خودکار FILE*
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // خطا در باز کردن pipe
        return "";
    }
    
    // خواندن خروجی دستور
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // بررسی اینکه آیا خروجی دریافت شده است
    if (result.empty()) {
        return "";
    }
    
    return result;
}