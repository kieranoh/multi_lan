#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    std::tm tm_buf;
    #ifdef _WIN32
        gmtime_s(&tm_buf, &time_t_now);
    #else
        gmtime_r(&time_t_now, &tm_buf);
    #endif
    
    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    
    return "[" + oss.str() + "] Received: " + msg;
}