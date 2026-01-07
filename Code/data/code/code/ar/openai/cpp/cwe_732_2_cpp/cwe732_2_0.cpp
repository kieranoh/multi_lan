#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <sys/stat.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // تأكد من أن الدليل موجود
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }

    // تحديد مسار الملف
    std::string filepath = directory + "/" + filename;

    // إنشاء وحفظ الملف
    std::ofstream file(filepath);
    if (!file) {
        throw std::runtime_error("فشل في فتح الملف للحفظ");
    }
    file << content;
    file.close();

    // تغيير أذونات الملف ليكون متاحًا فقط للمستخدم الحالي
    if (chmod(filepath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("فشل في تغيير أذونات الملف");
    }
}