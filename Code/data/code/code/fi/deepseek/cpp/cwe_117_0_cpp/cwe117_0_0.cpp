#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Hae nykyinen aika
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Muunna aika ISO-muotoon
    std::tm tm_buf;
    #ifdef _WIN32
        gmtime_s(&tm_buf, &time_t_now);
    #else
        gmtime_r(&time_t_now, &tm_buf);
    #endif
    
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    
    // Tarkista millisekunnit
    auto since_epoch = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(since_epoch);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch - seconds);
    
    // Lisää millisekunnit jos saatavilla
    if (milliseconds.count() > 0) {
        timestamp_stream << "." << std::setfill('0') << std::setw(3) << milliseconds.count();
    }
    
    // Luo lopullinen lokimerkintä
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] Vastaanotettu: " << msg;
    
    return log_stream.str();
}