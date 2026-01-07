#include <string>
#include <map>
#include <algorithm>

/**
 * اطلاعات ارائه شده را در یک نقشه هدر پاسخ موجود تحت نوع مشخص شده ذخیره می‌کند.
 * این تابع انواع اطلاعات زیر را در نظر می‌گیرد: 'lang'، 'encoding'، 'cache' که به ترتیب به عنوان کلیدهای 'Accept-Language'، 'Accept-Encoding' و 'Cache-Control' ذخیره می‌شوند.
 * اگر نوع اطلاعات مشخص شده معتبر باشد، هدر پاسخ به‌روزرسانی شده باید آن را داشته باشد. اگر مشکلی پیش بیاید، تابع باید هدر اصلی را بدون هیچ تغییری برگرداند.
 *
 * @param info_type نوع اطلاعاتی که باید در هدر ذخیره شود.
 * @param info_content محتوای اطلاعاتی که باید در هدر ذخیره شود.
 * @param header نقشه هدر پاسخ موجود.
 * @return نقشه هدر پاسخ به‌روزرسانی شده با اطلاعات ذخیره شده.
 */
void store_info_in_header(const std::string &info_type, const std::string &info_content, std::map<std::string, std::string> &header) {
    // تعیین کلید هدر بر اساس نوع اطلاعات
    std::string header_key;
    
    if (info_type == "lang") {
        header_key = "Accept-Language";
    } else if (info_type == "encoding") {
        header_key = "Accept-Encoding";
    } else if (info_type == "cache") {
        header_key = "Cache-Control";
    } else {
        // نوع اطلاعات نامعتبر است، هدر را بدون تغییر رها کن
        return;
    }
    
    // بررسی اینکه محتوای اطلاعات خالی نباشد (اختیاری - بستگی به نیاز دارد)
    if (info_content.empty()) {
        // اگر محتوای اطلاعات خالی باشد، می‌توانیم هدر را حذف کنیم یا کاری نکنیم
        // در اینجا تصمیم گرفتیم که اگر خالی باشد، هدر را حذف نکنیم و فقط مقدار خالی تنظیم کنیم
        header[header_key] = info_content;
    } else {
        // ذخیره اطلاعات در هدر
        header[header_key] = info_content;
    }
}