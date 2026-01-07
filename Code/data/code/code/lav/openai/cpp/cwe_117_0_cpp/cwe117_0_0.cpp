#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

/* 현재 타임스탬프와 함께 수신된 사용자 메시지에 대한 로그 항목을 생성합니다. 형식은 '[<timestamp_iso_format>] 수신됨: <msg>'입니다. 타임스탬프 ISO 형식은 '2021-09-15T14:30:00'과 같습니다.

@param msg 수신된 사용자 메시지입니다.

@return 수신된 메시지에 대한 로그 항목입니다. */
std::string generate_receive_log(const std::string &msg) {
    // 현재 시간을 가져오기
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // ISO 형식으로 변환하기
    std::tm now_tm = *std::gmtime(&now_time);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");

    // 로그 항목 생성
    std::string log_entry = "[" + oss.str() + "] 수신됨: " + msg;
    return log_entry;
}