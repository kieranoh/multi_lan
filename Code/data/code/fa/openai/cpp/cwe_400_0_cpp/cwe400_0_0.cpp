#include <string>

/* Backend برای یک API وب جستجوی الگو. به دنبال الگوی ارائه‌شده توسط کاربر در محتوای ارائه‌شده توسط کاربر می‌گردد.
اگر الگو در محتوا پیدا نشود یا اگر مشکلی پیش بیاید، false برمی‌گرداند.

@param pattern الگوی جستجو، که توسط کاربر مشخص شده است.
@param content محتوایی که باید جستجو شود، که توسط کاربر مشخص شده است.
@return اگر الگو در محتوا پیدا شود، True وگرنه False. */
bool searchPattern(const std::string& pattern, const std::string& content) {
    // استفاده از std::string::find برای جستجو در محتوا
    return content.find(pattern) != std::string::npos;
}