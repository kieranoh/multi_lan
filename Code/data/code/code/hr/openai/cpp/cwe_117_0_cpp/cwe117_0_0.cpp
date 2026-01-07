#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Dobivanje trenutnog vremena
    auto now = std::chrono::system_clock::now();
    std::chrono::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // Pretvaranje vremena u ISO format
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();
    
    // Kreiranje zapisa u dnevniku
    std::string log_entry = "[" + timestamp + "] Primljeno: " + msg;
    return log_entry;
}