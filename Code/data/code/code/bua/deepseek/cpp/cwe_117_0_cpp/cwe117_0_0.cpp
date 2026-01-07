#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 시스템 클록에서 가져옵니다
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // 로케일 독립적인 ISO 8601 형식으로 시간을 포맷팅합니다
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(std::gmtime(&time_t_now), "%Y-%m-%dT%H:%M:%S");
    
    // 최종 로그 문자열을 구성합니다
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] Received: " << msg;
    
    return log_stream.str();
}