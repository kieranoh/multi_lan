#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 가져옵니다.
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    // ISO 형식으로 타임스탬프를 생성합니다.
    std::tm now_tm = *std::gmtime(&now_time_t);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");

    // 로그 항목을 생성합니다.
    return "[" + oss.str() + "] 수신됨: " + msg;
}