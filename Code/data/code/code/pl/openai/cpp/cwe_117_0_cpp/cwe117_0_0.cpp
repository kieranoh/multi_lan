#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Pobierz aktualny czas
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);
    
    // Sformatuj znacznik czasu w formacie ISO 8601
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();
    
    // Zbuduj wpis dziennika
    std::string log_entry = "[" + timestamp + "] Odebrano: " + msg;
    return log_entry;
}