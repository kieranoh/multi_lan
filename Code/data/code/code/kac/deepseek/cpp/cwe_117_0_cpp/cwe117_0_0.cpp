#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 시스템 클록에서 가져옵니다.
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // ISO 8601 형식으로 시간을 포맷팅합니다.
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(std::localtime(&now_time), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp_iso = timestamp_stream.str();
    
    // 로그 항목을 생성합니다.
    std::string log_entry = "[" + timestamp_iso + "] Received: " + msg;
    return log_entry;
}