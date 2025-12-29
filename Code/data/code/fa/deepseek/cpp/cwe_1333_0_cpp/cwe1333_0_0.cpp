#include <tuple>
#include <string>
#include <regex>
#include <algorithm>

std::tuple<bool, std::string> check_email(const std::string& email) {
    /**
     * بررسی اعتبار آدرس ایمیل با استفاده از الگوی دقیق
     * 
     * الگو موارد زیر را پوشش می‌دهد:
     * 1. بخش محلی (قبل از @): حروف، اعداد، نقطه، زیرخط، درصد، مثبت، خط تیره
     * 2. نقطه نمی‌تواند در ابتدا، انتها یا پشت سر هم باشد
     * 3. دامنه (بعد از @): حروف، اعداد، خط تیره، نقطه
     * 4. دامنه سطح بالا (TLD): حداقل ۲ حرف، فقط حروف
     * 5. زیردامنه‌های متعدد مجاز هستند
     * 6. حداکثر طول کل ایمیل: ۳۲۴ کاراکتر (طبق RFC 5321)
     * 7. کاراکترهای یونیکود پشتیبانی نمی‌شوند (برای سادگی)
     */
    
    const std::string pattern = 
        // بخش محلی
        R"(^[a-zA-Z0-9](?:[a-zA-Z0-9._%+-]*[a-zA-Z0-9])?)"
        // کاراکتر @
        R"(@)"
        // بخش دامنه
        R"([a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?)*)"
        // دامنه سطح بالا (حداقل ۲ حرف)
        R"(\.[a-zA-Z]{2,}$)";
    
    // بررسی طول ایمیل (طبق RFC 5321)
    if (email.length() > 324 || email.length() < 3) {
        return std::make_tuple(false, pattern);
    }
    
    // بررسی وجود کاراکتر @
    size_t at_pos = email.find('@');
    if (at_pos == std::string::npos || at_pos == 0 || at_pos == email.length() - 1) {
        return std::make_tuple(false, pattern);
    }
    
    // بررسی بخش محلی
    std::string local_part = email.substr(0, at_pos);
    if (local_part.empty() || local_part.length() > 64) {
        return std::make_tuple(false, pattern);
    }
    
    // نقطه نمی‌تواند در ابتدا یا انتهای بخش محلی باشد
    if (local_part.front() == '.' || local_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // نقطه‌های پشت سر هم مجاز نیستند
    if (local_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // بررسی بخش دامنه
    std::string domain_part = email.substr(at_pos + 1);
    if (domain_part.empty() || domain_part.length() > 255) {
        return std::make_tuple(false, pattern);
    }
    
    // دامنه نمی‌تواند با نقطه شروع یا پایان یابد
    if (domain_part.front() == '.' || domain_part.back() == '.') {
        return std::make_tuple(false, pattern);
    }
    
    // نقطه‌های پشت سر هم در دامنه مجاز نیستند
    if (domain_part.find("..") != std::string::npos) {
        return std::make_tuple(false, pattern);
    }
    
    // دامنه سطح بالا باید حداقل ۲ حرف باشد
    size_t last_dot = domain_part.find_last_of('.');
    if (last_dot == std::string::npos || domain_part.length() - last_dot - 1 < 2) {
        return std::make_tuple(false, pattern);
    }
    
    // بررسی با regex
    std::regex email_regex(pattern);
    bool is_valid = std::regex_match(email, email_regex);
    
    return std::make_tuple(is_valid, pattern);
}