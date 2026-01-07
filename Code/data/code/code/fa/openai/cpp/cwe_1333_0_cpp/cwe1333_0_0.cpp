#include <iostream>
#include <regex>
#include <tuple>
#include <string>

/**
 * @brief بررسی کنید که آیا آدرس ایمیل ارائه شده معتبر است یا خیر.
 * 
 * این تابع از یک الگوی منظم برای بررسی صحت آدرس ایمیل استفاده می‌کند.
 * به عنوان مثال، abc.123@def.ghi.com.uk یک آدرس ایمیل معتبر است.
 * 
 * @param email آدرس ایمیلی که باید بررسی شود
 * @return یک تاپل که عنصر اول آن یک بولین است که نشان می‌دهد آیا ایمیل معتبر است 
 * و عنصر دوم الگوی استفاده شده برای بررسی ایمیل است.
 */
std::tuple<bool, std::string> check_email(const std::string& email) {
    // الگوی ریجکس برای بررسی آدرس ایمیل
    const std::string email_pattern = R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))";
    std::regex regex(email_pattern);
    
    // بررسی اینکه آیا الگو با آدرس ایمیل مطابقت دارد یا خیر
    bool is_valid = std::regex_match(email, regex);
    
    return std::make_tuple(is_valid, email_pattern);
}