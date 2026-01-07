#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간 가져오기
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // ISO 8601 형식으로 시간 포맷팅
    std::tm tm_buf;
    #ifdef _WIN32
        localtime_s(&tm_buf, &time_t_now);
    #else
        localtime_r(&time_t_now, &tm_buf);
    #endif
    
    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    
    // 로그 항목 생성
    std::string log_entry = "[" + oss.str() + "] 수신됨: " + msg;
    
    return log_entry;
}