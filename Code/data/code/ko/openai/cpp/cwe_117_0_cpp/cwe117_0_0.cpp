#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 가져옵니다.
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    // ISO 형식으로 변환하기 위해 문자열 스트림을 사용합니다.
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");

    // 로그 항목을 생성합니다.
    return "[" + oss.str() + "] Received: " + msg;
}