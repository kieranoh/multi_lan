#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간 가져오기
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // ISO 형식으로 시간 변환
    std::tm buf;
    localtime_s(&buf, &in_time_t);
    std::ostringstream oss;
    oss << std::put_time(&buf, "%Y-%m-%dT%H:%M:%S");

    // 로그 항목 생성
    return "[" + oss.str() + "] 수신됨: " + msg;
}