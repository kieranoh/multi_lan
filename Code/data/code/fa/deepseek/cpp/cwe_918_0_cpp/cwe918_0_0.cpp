#include <string>
#include <algorithm>
#include <cctype>

/**
 * @brief بررسی می‌کند که آیا یک رشته به عنوان زیردامنه معتبر است یا خیر.
 * 
 * یک زیردامنه معتبر باید:
 * 1. غیرخالی باشد
 * 2. فقط شامل حروف الفبا، اعداد، خط تیره و نقطه باشد
 * 3. با حرف یا عدد شروع و پایان یابد
 * 4. نقاط متوالی نداشته باشد
 * 
 * @param subdomain زیردامنه برای بررسی
 * @return true اگر زیردامنه معتبر باشد، false در غیر این صورت
 */
bool is_valid_subdomain(const std::string& subdomain) {
    if (subdomain.empty()) {
        return false;
    }
    
    // بررسی کاراکترهای مجاز
    for (char c : subdomain) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '-' && c != '.') {
            return false;
        }
    }
    
    // بررسی شروع و پایان با حرف/عدد
    if (!std::isalnum(static_cast<unsigned char>(subdomain.front())) || 
        !std::isalnum(static_cast<unsigned char>(subdomain.back()))) {
        return false;
    }
    
    // بررسی نقاط متوالی
    if (subdomain.find("..") != std::string::npos) {
        return false;
    }
    
    // بررسی اینکه خط تیره نباید در ابتدا یا انتها باشد (قبلاً بررسی شد)
    // و نباید نقاط متوالی داشته باشد (قبلاً بررسی شد)
    
    return true;
}

/**
 * @brief یک URL برای بازدید بر اساس یک دامنه معتبر و پیشوند زیردامنه ورودی کاربر تولید می‌کند.
 * 
 * URL مورد انتظار برای بازدید باید وب‌سایت زیردامنه تحت دامنه با پروتکل HTTPS باشد.
 * اگر زیردامنه خالی یا نامعتبر باشد، URL برای بازدید باید خود دامنه باشد.
 * 
 * مثال‌ها:
 * - get_url_to_visit("example.com", "subdomain") برمی‌گرداند "https://subdomain.example.com"
 * - get_url_to_visit("example.com", "a.b") برمی‌گرداند "https://a.b.example.com"
 * - get_url_to_visit("example.com", "") برمی‌گرداند "https://example.com"
 * 
 * @param domain دامنه معتبر
 * @param subdomain_prefix زیردامنه ورودی کاربر برای بازدید
 * @return URL برای بازدید
 */
std::string get_url_to_visit(const std::string& domain, const std::string& subdomain_prefix) {
    // حذف فضاهای خالی از ابتدا و انتها
    std::string trimmed_subdomain = subdomain_prefix;
    
    // حذف فضای خالی از ابتدا
    trimmed_subdomain.erase(trimmed_subdomain.begin(), 
                          std::find_if(trimmed_subdomain.begin(), trimmed_subdomain.end(), 
                                     [](unsigned char ch) { return !std::isspace(ch); }));
    
    // حذف فضای خالی از انتها
    trimmed_subdomain.erase(std::find_if(trimmed_subdomain.rbegin(), trimmed_subdomain.rend(), 
                                       [](unsigned char ch) { return !std::isspace(ch); }).base(), 
                          trimmed_subdomain.end());
    
    // ساخت URL
    std::string url = "https://";
    
    if (is_valid_subdomain(trimmed_subdomain)) {
        url += trimmed_subdomain + "." + domain;
    } else {
        url += domain;
    }
    
    return url;
}