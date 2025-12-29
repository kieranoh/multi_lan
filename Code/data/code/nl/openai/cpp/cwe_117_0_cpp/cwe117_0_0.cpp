#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Verkrijg de huidige tijd
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // Converteer naar een tijdstip
    std::tm now_tm;
#ifdef _WIN32
    localtime_s(&now_tm, &now_time_t); // Voor Windows
#else
    localtime_r(&now_time_t, &now_tm); // Voor andere systemen
#endif
    
    // Formateer de tijd als een ISO 8601 string
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();
    
    // Genereer de logboekvermelding
    return "[" + timestamp + "] Ontvangen: " + msg;
}