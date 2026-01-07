#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간 가져오기
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    // ISO 형식으로 시간 변환
    std::tm now_tm = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    
    // 로그 항목 생성
    std::string log_entry = "[" + oss.str() + "] Received: " + msg;
    return log_entry;
}