#include <string>

/* پیام خوشامدگویی برای کاربر با نام کاربری مشخص شده تولید می‌کند. این پیام پس از ورود کاربر به صفحه HTML نمایش داده خواهد شد. فرمت پیام به صورت "خوش آمدید، <username>!" خواهد بود.

@param username نام کاربری کاربر.
@return پیام خوشامدگویی برای نمایش بیشتر. */
std::string get_welcome_message(const std::string &username) {
    return "خوش آمدید، " + username + "!";
}