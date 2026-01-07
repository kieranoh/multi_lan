#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간 가져오기
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    // ISO 포맷으로 타임스탬프 생성
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");

    // 로그 항목 생성
    std::string log_entry = "[" + oss.str() + "] Received: " + msg;
    
    return log_entry;
}