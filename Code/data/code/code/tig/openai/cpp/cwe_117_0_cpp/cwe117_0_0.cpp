#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 가져옵니다.
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // ISO 8601 형식으로 시간을 변환합니다.
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&now_time), "%Y-%m-%dT%H:%M:%S");

    // 로그 항목을 생성하여 반환합니다.
    return "[" + oss.str() + "] Received: " + msg;
}