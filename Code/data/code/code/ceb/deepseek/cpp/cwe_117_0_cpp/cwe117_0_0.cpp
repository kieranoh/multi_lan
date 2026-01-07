#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 얻기 위해 system_clock 사용
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // tm 구조체로 변환 (로컬 시간)
    std::tm tm_now;
    localtime_r(&time_t_now, &tm_now); // POSIX 함수, Windows에서는 localtime_s 사용
    
    // ISO 8601 형식으로 문자열 생성
    std::ostringstream oss;
    oss << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    
    // 로그 항목 생성
    std::string log_entry = "[" + oss.str() + "] 수신됨: " + msg;
    
    return log_entry;
}