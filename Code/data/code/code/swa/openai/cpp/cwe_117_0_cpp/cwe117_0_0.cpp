#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시각을 얻기
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // ISO 형식으로 변환하기 위해 struct tm 사용
    std::tm now_tm = *std::localtime(&now_time);
    std::ostringstream oss;
    
    // ISO 8601 형식으로 시각을 포맷하기
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();
    
    // 로그 항목 생성
    std::string log_entry = "[" + timestamp + "] Received: " + msg;
    return log_entry;
}