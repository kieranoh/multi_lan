#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Dobijanje trenutnog vremena
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // Pretvaranje u lokalno vreme
    std::tm local_tm = *std::localtime(&now_time_t);
    
    // Formiranje stringa za vremenski pečat u ISO formatu
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();
    
    // Formiranje zapisa u dnevniku
    return "[" + timestamp + "] Primljeno: " + msg;
}