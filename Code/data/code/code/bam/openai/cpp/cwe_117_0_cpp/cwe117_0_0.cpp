#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 가져옵니다.
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    
    // ISO 포맷으로 변환하기 위한 스트림 준비
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%Y-%m-%dT%H:%M:%S");
    
    // 로그 항목 생성
    return "[" + oss.str() + "] Received: " + msg;
}