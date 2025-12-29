#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // طول کلید RSA
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // استفاده از یک آرایه برای ذخیره خروجی فرمان
    std::array<char, 128> buffer;
    std::string result;
    
    // اجرای فرمان و ذخیره خروجی
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return NULL; // اگر خطا رخ داد، NULL برگردانید
    }
    
    // خواندن خروجی فرمان
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? NULL : result; // اگر نتیجه خالی باشد، NULL برگردانید
}