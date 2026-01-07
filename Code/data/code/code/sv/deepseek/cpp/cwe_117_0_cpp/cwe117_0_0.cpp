#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Hämta nuvarande tid
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Konvertera till lokal tid
    std::tm local_time = *std::localtime(&time_t_now);
    
    // Formatera till ISO-format (YYYY-MM-DDTHH:MM:SS)
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&local_time, "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = timestamp_stream.str();
    
    // Skapa loggposten
    return "[" + timestamp + "] Mottaget: " + msg;
}