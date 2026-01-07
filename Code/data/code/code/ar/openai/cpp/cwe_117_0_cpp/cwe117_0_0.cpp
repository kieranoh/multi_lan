#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // الحصول على الوقت الحالي
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // تحويل الوقت إلى تنسيق ISO
    std::tm now_tm = *std::localtime(&now_time_t);
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");

    // إنشاء إدخال السجل
    std::string log_entry = "[" + timestamp_stream.str() + "] تم الاستلام: " + msg;
    return log_entry;
}