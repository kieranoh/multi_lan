#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstring>

std::string get_ls_result(const std::string &dir_path) {
    // بناء أمر ls -l مع المسار المحدد
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // فتح قناة للقراءة من إخراج الأمر
    std::array<char, 128> buffer;
    std::string result;
    
    // استخدام popen لتنفيذ الأمر وقراءة الإخراج
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // فشل في فتح القناة
        return "";
    }
    
    // قراءة الإخراج سطرًا بسطر
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // التحقق مما إذا كان الإخراج فارغًا (قد يشير إلى خطأ)
    // إذا كان الإخراج فارغًا أو يحتوي فقط على أحرف بيضاء، نعيد سلسلة فارغة
    if (result.empty()) {
        return "";
    }
    
    // التحقق مما إذا كان الإخراج يحتوي على رسائل خطأ (على الرغم من إعادة توجيه stderr)
    // قد تظهر بعض رسائل الخطأ في stdout
    if (result.find("No such file or directory") != std::string::npos ||
        result.find("Permission denied") != std::string::npos ||
        result.find("cannot access") != std::string::npos) {
        return "";
    }
    
    return result;
}