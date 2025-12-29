#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Şu anki zaman damgasını al
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Zaman damgasını ISO formatında oluştur
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S");

    // Günlük girişini oluştur
    std::string log_entry = "[" + oss.str() + "] Alındı: " + msg;

    return log_entry;
}