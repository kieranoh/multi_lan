#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간 가져오기
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);

    // ISO 형식으로 시간 문자열 생성
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_t), "%Y-%m-%dT%H:%M:%S");

    // 로그 항목 생성
    return "[" + oss.str() + "] Received: " + msg;
}