#include <string>
#include <algorithm>
#include <cctype>

std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // التحقق مما إذا كان معرف المستخدم فارغًا أو غير صالح
    if (user_id.empty()) {
        return "";
    }
    
    // التحقق مما إذا كان معرف المستخدم يحتوي على أحرف غير مسموح بها
    // نتحقق من وجود أحرف غير قابلة للطباعة أو مسافات
    bool is_valid = std::all_of(user_id.begin(), user_id.end(), [](char c) {
        return std::isgraph(c); // يتحقق من أن الحرف قابل للطباعة وليس مسافة
    });
    
    if (!is_valid) {
        return "";
    }
    
    // التحقق مما إذا كان معرف المستخدم يحتوي على مسافات في البداية أو النهاية
    if (std::isspace(user_id.front()) || std::isspace(user_id.back())) {
        return "";
    }
    
    // بناء عنوان URL
    // إزالة الشرطة المائلة الأخيرة من api_url إذا كانت موجودة
    std::string cleaned_api_url = api_url;
    if (!cleaned_api_url.empty() && cleaned_api_url.back() == '/') {
        cleaned_api_url.pop_back();
    }
    
    // إضافة معرف المستخدم إلى عنوان URL
    return cleaned_api_url + "/" + user_id;
}