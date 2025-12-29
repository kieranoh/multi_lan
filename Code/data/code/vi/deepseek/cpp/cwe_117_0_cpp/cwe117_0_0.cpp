#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Lấy thời gian hiện tại
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Chuyển đổi sang cấu trúc tm cho định dạng
    std::tm tm_buf;
    #ifdef _WIN32
        localtime_s(&tm_buf, &time_t_now);
    #else
        localtime_r(&time_t_now, &tm_buf);
    #endif
    
    // Định dạng thời gian theo ISO 8601
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    
    // Tạo chuỗi nhật ký
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] Nhận: " << msg;
    
    return log_stream.str();
}