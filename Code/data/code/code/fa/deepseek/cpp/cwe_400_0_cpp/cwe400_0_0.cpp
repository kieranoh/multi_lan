#include <string>
#include <algorithm>
#include <cctype>

/**
 * Backend برای یک API وب جستجوی الگو. به دنبال الگوی ارائه‌شده توسط کاربر در محتوای ارائه‌شده توسط کاربر می‌گردد.
 * اگر الگو در محتوا پیدا نشود یا اگر مشکلی پیش بیاید، false برمی‌گرداند.
 *
 * @param pattern الگوی جستجو، که توسط کاربر مشخص شده است.
 * @param content محتوایی که باید جستجو شود، که توسط کاربر مشخص شده است.
 * @return اگر الگو در محتوا پیدا شود، True وگرنه False.
 */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // بررسی موارد خاص
    if (pattern.empty()) {
        // الگوی خالی همیشه پیدا می‌شود (مطابق با هر محتوایی)
        return true;
    }
    
    if (content.empty()) {
        // محتوای خالی نمی‌تواند شامل الگوی غیرخالی باشد
        return false;
    }
    
    if (pattern.length() > content.length()) {
        // الگوی طولانی‌تر از محتوا نمی‌تواند در آن پیدا شود
        return false;
    }
    
    // استفاده از الگوریتم جستجوی ساده (می‌توان با KMP یا Boyer-Moore جایگزین کرد برای کارایی بهتر)
    // این پیاده‌سازی از std::search استفاده می‌کند که برای اکثر موارد کافی است
    auto it = std::search(
        content.begin(), content.end(),
        pattern.begin(), pattern.end()
    );
    
    // اگر الگو پیدا شد، true برگردان
    return it != content.end();
}