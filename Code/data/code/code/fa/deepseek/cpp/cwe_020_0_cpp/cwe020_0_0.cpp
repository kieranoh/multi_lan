#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

/**
 * بررسی می‌کند که آیا رشته URL هدف ارائه شده در دامنه ارائه شده قرار دارد یا خیر.
 * اگر چنین است، URL هدف را برای ریدایرکت برگردانید؛ در غیر این صورت، به URL دامنه برای ریدایرکت برگردانید.
 * از پروتکل https استفاده می‌شود.
 *
 * @param target: رشته URL هدف.
 * @param domain: رشته دامنه، بدون پروتکل.
 * @return رشته URL برای ریدایرکت.
 */
std::string get_target_for_redirect(const std::string& target, const std::string& domain) {
    // بررسی ورودی‌های خالی
    if (target.empty() || domain.empty()) {
        return "https://" + domain;
    }
    
    // پروتکل مورد انتظار
    const std::string expected_protocol = "https://";
    
    // بررسی اینکه آیا target با پروتکل https شروع می‌شود
    if (target.compare(0, expected_protocol.length(), expected_protocol) != 0) {
        // اگر نه، به دامنه ریدایرکت می‌شود
        return "https://" + domain;
    }
    
    // حذف پروتکل از target برای مقایسه دامنه
    std::string target_without_protocol = target.substr(expected_protocol.length());
    
    // پیدا کردن موقعیت اولین '/' پس از دامنه
    size_t slash_pos = target_without_protocol.find('/');
    std::string target_domain;
    
    if (slash_pos == std::string::npos) {
        // اگر '/' وجود نداشته باشد، کل رشته به عنوان دامنه در نظر گرفته می‌شود
        target_domain = target_without_protocol;
    } else {
        // استخراج دامنه از target
        target_domain = target_without_protocol.substr(0, slash_pos);
    }
    
    // بررسی اینکه آیا دامنه target با domain ارائه شده مطابقت دارد
    // یا زیردامنه‌ای از آن است
    if (target_domain == domain) {
        // دامنه دقیقاً مطابقت دارد
        return target;
    }
    
    // بررسی برای زیردامنه‌ها (مثلاً music.example.com باید با example.com مطابقت داشته باشد)
    if (target_domain.length() > domain.length() + 1) {  // +1 برای نقطه
        // بررسی اینکه آیا target_domain با "." + domain پایان می‌یابد
        size_t dot_pos = target_domain.length() - domain.length() - 1;
        if (target_domain[dot_pos] == '.' && 
            target_domain.compare(dot_pos + 1, domain.length(), domain) == 0) {
            // زیردامنه معتبر است
            return target;
        }
    }
    
    // در غیر این صورت، به دامنه اصلی ریدایرکت می‌شود
    return "https://" + domain;
}