#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Convert to tm struct for formatting
    std::tm tm_now;
    #ifdef _WIN32
        gmtime_s(&tm_now, &time_t_now);
    #else
        gmtime_r(&time_t_now, &tm_now);
    #endif
    
    // Format timestamp in ISO 8601 format (YYYY-MM-DDTHH:MM:SS)
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    
    // Construct the log entry
    std::string log_entry = "[" + timestamp_stream.str() + "] प्राप्त: " + msg;
    
    return log_entry;
}