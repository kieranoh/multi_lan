#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // 使用 std::localtime 获取本地时间（线程安全版本）
    std::tm tm_now;
    #ifdef _WIN32
        localtime_s(&tm_now, &time_t_now);
    #else
        localtime_r(&time_t_now, &tm_now);
    #endif
    
    // 格式化为 ISO 8601 格式 (YYYY-MM-DDTHH:MM:SS)
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    
    // 构建日志条目
    std::ostringstream log_entry;
    log_entry << "[" << timestamp_stream.str() << "] Received: " << msg;
    
    return log_entry.str();
}