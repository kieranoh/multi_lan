#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // التحقق مما إذا كانت البادئة الفرعية فارغة أو غير صالحة
    bool is_subdomain_valid = false;
    
    // البادئة الفرعية تعتبر صالحة إذا كانت تحتوي على حرف واحد على الأقل غير مسافة
    if (!subdomain_prefix.empty()) {
        // التحقق مما إذا كانت تحتوي على حرف واحد على الأقل غير مسافة
        for (char c : subdomain_prefix) {
            if (!std::isspace(static_cast<unsigned char>(c))) {
                is_subdomain_valid = true;
                break;
            }
        }
    }
    
    // بناء عنوان URL
    std::string url = "https://";
    
    if (is_subdomain_valid) {
        // إضافة البادئة الفرعية
        url += subdomain_prefix;
        
        // إضافة نقطة فاصلة فقط إذا لم تكن البادئة الفرعية تنتهي بنقطة
        if (!subdomain_prefix.empty() && subdomain_prefix.back() != '.') {
            url += ".";
        }
    }
    
    // إضافة النطاق
    url += domain;
    
    return url;
}