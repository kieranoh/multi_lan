#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // वर्तमान समय प्राप्त करें
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // समय को ISO प्रारूप में परिवर्तित करें
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%dT%H:%M:%S");

    // लॉग प्रविष्टि बनाएं
    return "[" + oss.str() + "] प्राप्त: " + msg;
}