#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // دریافت زمان فعلی
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // تبدیل زمان به فرمت زمان محلی
    std::tm now_tm = *std::localtime(&now_time_t);
    
    // ساختاردهی خروجی به فرمت ISO
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "[%Y-%m-%dT%H:%M:%S] دریافت شد: ") << msg;
    
    return oss.str();
}