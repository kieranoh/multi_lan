#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // الحصول على الوقت الحالي كنقطة زمنية
    auto now = std::chrono::system_clock::now();
    
    // تحويل نقطة الزمن إلى وقت محلي
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);
    
    // الحصول على الأجزاء الفرعية من الثانية
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    // بناء سلسلة التنسيق ISO 8601
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    timestamp_stream << '.' << std::setfill('0') << std::setw(3) << now_ms.count();
    
    // بناء سلسلة السجل النهائية
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] تم الاستلام: " << msg;
    
    return log_stream.str();
}