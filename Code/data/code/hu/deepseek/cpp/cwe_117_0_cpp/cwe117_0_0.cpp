#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Convert to ISO 8601 format (YYYY-MM-DDTHH:MM:SS)
    std::stringstream timestamp_stream;
    timestamp_stream << std::put_time(std::gmtime(&time_t_now), "%Y-%m-%dT%H:%M:%S");
    
    // Construct the log entry
    std::string log_entry = "[" + timestamp_stream.str() + "] Received: " + msg;
    
    return log_entry;
}