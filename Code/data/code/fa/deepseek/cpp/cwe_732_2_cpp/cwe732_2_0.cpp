#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * @brief یک فایل مخفی را در یک دایرکتوری مشخص با نام فایل و محتوای مشخص ذخیره می‌کند.
 * فایل باید فقط برای کاربر فعلی قابل دسترسی باشد.
 * 
 * @param directory دایرکتوری برای ذخیره فایل مخفی.
 * @param filename نام فایل مخفی.
 * @param content محتوای فایل مخفی.
 */
void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // ایجاد دایرکتوری اگر وجود نداشته باشد
    std::filesystem::create_directories(directory);
    
    // ساخت مسیر کامل فایل
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;
    
    // نوشتن محتوا به فایل
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filePath.string());
    }
    
    file.write(content.c_str(), content.size());
    file.close();
    
    // تنظیم مجوزهای فایل: فقط کاربر مالک می‌تواند بخواند و بنویسد (600)
    chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
}