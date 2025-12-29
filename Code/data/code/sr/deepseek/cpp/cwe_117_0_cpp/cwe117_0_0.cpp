#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Dobijanje trenutnog vremena
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Konvertovanje u lokalno vreme za formatiranje
    std::tm tm_now = *std::localtime(&time_t_now);
    
    // Formatiranje u ISO format (YYYY-MM-DDTHH:MM:SS)
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = timestamp_stream.str();
    
    // Sastavljanje finalnog zapisa
    return "[" + timestamp + "] Primljeno: " + msg;
}