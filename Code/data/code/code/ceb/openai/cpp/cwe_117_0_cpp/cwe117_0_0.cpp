#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간 가져오기
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // ISO 형식의 타임스탬프 생성
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&now_time), "%Y-%m-%dT%H:%M:%S");

    // 로그 항목 생성
    std::string log_entry = "[" + oss.str() + "] 수신됨: " + msg;
    return log_entry;
}