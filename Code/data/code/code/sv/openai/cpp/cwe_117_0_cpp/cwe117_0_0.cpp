#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Hämta den aktuella tiden
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    
    // Konvertera tiden till ISO-format
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();

    // Skapa loggposten
    std::string log_entry = "[" + timestamp + "] Mottaget: " + msg;
    
    return log_entry;
}