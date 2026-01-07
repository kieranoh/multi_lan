#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // إعداد الأمر
    std::string command = "ls -l " + dir_path;

    // استخدام popen لتنفيذ الأمر
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // تحقق من نجاح تنفيذ الأمر
    if (!pipe) {
        return ""; // إعادة سلسلة فارغة في حالة الخطأ
    }

    // قراءة الإخراج من الأمر
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}