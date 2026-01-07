#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

std::string read_file_from_dir(const std::string &filename, const std::string &dir_path) {
    // إنشاء مسار كامل للملف
    std::filesystem::path file_path = std::filesystem::path(dir_path) / filename;
    
    // التحقق من وجود الملف وإمكانية قراءته
    if (!std::filesystem::exists(file_path) || 
        !std::filesystem::is_regular_file(file_path) ||
        !std::filesystem::is_readable(file_path)) {
        return "";
    }
    
    // فتح الملف للقراءة
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return "";
    }
    
    // قراءة محتوى الملف
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    // إغلاق الملف وإعادة المحتوى
    file.close();
    return buffer.str();
}