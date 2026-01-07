#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간의 타임스탬프를 가져옵니다.
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // ISO 형식의 타임스탬프를 생성합니다.
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S");

    // 로그 메시지를 형식에 맞게 반환합니다.
    return "[" + oss.str() + "] 수신됨: " + msg;
}