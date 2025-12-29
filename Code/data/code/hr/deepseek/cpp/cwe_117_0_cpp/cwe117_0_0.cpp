#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Dobijanje trenutnog vremena
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Konverzija u lokalno vrijeme
    std::tm local_time = *std::localtime(&time_t_now);
    
    // Formatiranje u ISO format (YYYY-MM-DDTHH:MM:SS)
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&local_time, "%Y-%m-%dT%H:%M:%S");
    
    // Sastavljanje konačnog zapisa
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] Primljeno: " << msg;
    
    return log_stream.str();
}