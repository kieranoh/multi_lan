#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 시스템 클록에서 가져옵니다
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // 밀리초 부분을 계산합니다
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration) - seconds;
    
    // 로케일을 저장하고 C 로케일로 설정합니다
    std::ostringstream oss;
    oss << std::put_time(std::gmtime(&time_t_now), "%Y-%m-%dT%H:%M:%S");
    
    // ISO 8601 형식으로 타임스탬프 생성 (밀리초 포함)
    oss << "." << std::setfill('0') << std::setw(3) << milliseconds.count();
    
    // 최종 로그 문자열 생성
    return "[" + oss.str() + "] Received: " + msg;
}