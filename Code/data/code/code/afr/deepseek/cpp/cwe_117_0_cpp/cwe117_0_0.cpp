#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 시스템 클록에서 가져옵니다.
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    // ISO 8601 형식으로 타임스탬프를 생성합니다.
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(std::gmtime(&time), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = timestamp_stream.str();
    
    // 최종 로그 항목을 구성합니다.
    std::ostringstream log_stream;
    log_stream << "[" << timestamp << "] 수신됨: " << msg;
    
    return log_stream.str();
}