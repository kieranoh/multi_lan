#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// تابع اعلام شده برای اجرای دستورات شل
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // طول کلید DSA (می‌تواند تغییر کند)
    const int key_length = 2048;
    
    // ایجاد نام فایل موقت برای پارامترهای DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // خطا در ایجاد فایل موقت
        return "";
    }
    
    // بستن فایل‌دسکریپتور چون فقط به نام فایل نیاز داریم
    close(fd);
    
    // مرحله 1: تولید پارامترهای DSA
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length);
    
    std::string param_result = execute_command(param_command);
    
    // بررسی موفقیت‌آمیز بودن اجرای دستور
    if (param_result.empty()) {
        // حذف فایل موقت در صورت خطا
        remove(param_filename);
        return "";
    }
    
    // مرحله 2: تولید کلید خصوصی DSA از پارامترها
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string key_result = execute_command(key_command);
    
    // حذف فایل پارامترهای موقت
    remove(param_filename);
    
    // بررسی موفقیت‌آمیز بودن تولید کلید
    if (key_result.empty()) {
        return "";
    }
    
    // بازگرداندن کلید خصوصی DSA در فرمت PEM
    return key_result;
}