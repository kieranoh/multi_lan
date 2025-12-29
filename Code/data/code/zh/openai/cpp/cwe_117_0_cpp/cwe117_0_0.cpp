#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // 转换为 ISO 格式的时间戳
    std::tm now_tm = *std::localtime(&now_time_t);
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    
    // 生成日志条目
    return "[" + oss.str() + "] Received: " + msg;
}