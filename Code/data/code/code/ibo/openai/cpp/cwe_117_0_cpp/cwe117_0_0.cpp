#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 가져옵니다.
    auto now = std::chrono::system_clock::now();
    // 현재 시간을 ISO 형식으로 변환하기 위한 time_t로 변환합니다.
    std::chrono::time_point<std::chrono::system_clock> tp = now;
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    
    // ISO 형식으로 변환하기 위해 tm 구조체를 사용합니다.
    std::tm buf;
    localtime_s(&buf, &time);
    
    // ISO 형식을 위한 스트림을 사용합니다.
    std::ostringstream oss;
    oss << std::put_time(&buf, "%Y-%m-%dT%H:%M:%S");
    
    // 로그 항목을 생성합니다.
    return "[" + oss.str() + "] Received: " + msg;
}