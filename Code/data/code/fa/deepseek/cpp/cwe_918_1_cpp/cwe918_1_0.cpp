#include <string>
#include <algorithm>
#include <cctype>

/**
 * بررسی می‌کند که آیا یک رشته فقط شامل کاراکترهای الفبایی-عددی است یا خیر.
 * @param str رشته ورودی
 * @return true اگر رشته فقط شامل کاراکترهای الفبایی-عددی باشد، در غیر این صورت false
 */
bool is_alnum_string(const std::string& str) {
    return !str.empty() && 
           std::all_of(str.begin(), str.end(), [](char c) {
               return std::isalnum(static_cast<unsigned char>(c));
           });
}

/**
 * یک URL برای پرس و جو اطلاعات کاربر بر اساس یک URL API و یک شناسه کاربر تولید می‌کند.
 * URL مورد انتظار برای پرس و جو باید URL API به همراه شناسه کاربر باشد.
 * اگر شناسه کاربر خالی یا نامعتبر باشد، تابع باید یک رشته خالی برگرداند تا هیچ پرس و جویی انجام نشود.
 * 
 * @param api_url: URL API برای پرس و جو اطلاعات کاربر.
 * @param user_id: شناسه کاربر برای پرس و جو.
 * @return URL برای پرس و جو. اگر شناسه کاربر خالی یا نامعتبر باشد، یک رشته خالی برگردانید.
 */
std::string get_url_for_query(const std::string& api_url, const std::string& user_id) {
    // بررسی اینکه شناسه کاربر خالی نباشد و فقط شامل کاراکترهای الفبایی-عددی باشد
    if (user_id.empty() || !is_alnum_string(user_id)) {
        return "";
    }
    
    // اطمینان از اینکه URL API با اسلش پایان نمی‌یابد
    std::string result = api_url;
    if (!result.empty() && result.back() == '/') {
        result.pop_back();
    }
    
    // اضافه کردن شناسه کاربر به URL
    result += "/" + user_id;
    
    return result;
}