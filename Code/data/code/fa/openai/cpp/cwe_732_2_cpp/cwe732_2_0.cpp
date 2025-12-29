#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // ایجاد مسیر کامل برای فایل
    std::string filePath = directory + "/" + filename;

    // ایجاد و باز کردن فایل برای نوشتن
    std::ofstream outFile(filePath);
    
    if (!outFile) {
        std::cerr << "خطا در ایجاد فایل: " << filePath << std::endl;
        return;
    }
    
    // نوشتن محتوا به فایل
    outFile << content;
    outFile.close();

    // تنظیم مجوزهای فایل برای اینکه فقط کاربر فعلی به آن دسترسی داشته باشد
    mode_t mode = S_IRUSR | S_IWUSR; // فقط خواندن و نوشتن برای کاربر
    if (chmod(filePath.c_str(), mode) != 0) {
        std::cerr << "خطا در تنظیم مجوزهای فایل: " << filePath << std::endl;
    }
}