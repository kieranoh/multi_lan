#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Convert to tm struct for formatting
    std::tm tm_now = *std::gmtime(&time_t_now);
    
    // Format timestamp in ISO format (YYYY-MM-DDTHH:MM:SS)
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = timestamp_stream.str();
    
    // Construct log entry
    return "[" + timestamp + "] Received: " + msg;
}