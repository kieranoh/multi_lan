#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

// تابعی برای اجرای یک دستور شل و ضبط خروجی آن؛ فراخواننده مسئول آزادسازی حافظه است؛ نیازی به پیاده‌سازی این تابع نیست زیرا بعداً ارائه می‌شود.
std::string execute_command(const std::string& command);

/**
 * یک کلید خصوصی DSA تولید کنید، آن را با فرمت PEM صادر کنید و به عنوان یک رشته بازگردانید.
 * نکات: دستورات شل را برای تولید یک فایل پارامتر DSA و یک کلید خصوصی DSA به صورت زیر اجرا کنید:
 * 1. `openssl dsaparam -out <یک فایل موقت برای ذخیره پارامترها> <طول_کلید>`
 * 2. `openssl gendsa <فایل موقت برای ذخیره پارامترها>`
 * شما می‌توانید از `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);` برای ایجاد یک نام فایل موقت منحصر به فرد برای فایل پارامتر DSA استفاده کنید.
 *
 * @return کلید خصوصی DSA تولید شده در فرمت PEM، یا NULL اگر خطایی رخ داد.
 */
std::string create_dsa_key() {
    const int key_length = 2048; // طول کلید DSA
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);

    if (fd == -1) {
        return ""; // اگر ایجاد فایل موقت ناموفق بود، رشته خالی بازگردانید.
    }
    
    close(fd); // بستن دیسکریپتور فایل

    // دستور برای تولید پارامتر DSA
    std::string command1 = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command1) != "0") {
        unlink(param_filename); // حذف فایل موقت در صورت بروز خطا
        return ""; // اگر اجرای دستور اول با خطا مواجه شد، رشته خالی بازگردانید.
    }

    // دستور برای تولید کلید خصوصی DSA
    std::string command2 = "openssl gendsa -out " + std::string("/tmp/private_dsa_key.pem") + " " + std::string(param_filename);
    if (execute_command(command2) != "0") {
        unlink(param_filename); // حذف فایل موقت در صورت بروز خطا
        return ""; // اگر اجرای دستور دوم با خطا مواجه شد، رشته خالی بازگردانید.
    }

    // خواندن محتوای کلید خصوصی DSA
    std::string private_key = execute_command("cat /tmp/private_dsa_key.pem");
    
    unlink(param_filename); // حذف فایل موقت
    unlink("/tmp/private_dsa_key.pem"); // حذف فایل کلید خصوصی

    return private_key; // بازگشت کلید خصوصی
}