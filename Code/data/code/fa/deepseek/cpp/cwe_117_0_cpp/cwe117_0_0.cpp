#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // دریافت زمان فعلی
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // تبدیل به ساختار tm برای فرمت‌دهی
    std::tm tm_now = *std::gmtime(&time_t_now);
    
    // ایجاد رشته با فرمت ISO 8601 (YYYY-MM-DDTHH:MM:SS)
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = timestamp_stream.str();
    
    // ایجاد ورودی لاگ نهایی
    return "[" + timestamp + "] دریافت شد: " + msg;
}