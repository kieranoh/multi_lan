#include <string>
#include <iostream>

bool searchPattern(const std::string& pattern, const std::string& content) {
    // التحقق من صحة المدخلات
    if (pattern.empty() || content.empty()) {
        return false; // إرجاع false إذا كانت المدخلات فارغة
    }
    
    // البحث عن النمط في المحتوى
    size_t found = content.find(pattern);
    
    // إرجاع true إذا تم العثور على النمط، و false خلاف ذلك
    return (found != std::string::npos);
}