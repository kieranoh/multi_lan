#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Získání aktuálního času
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Získání milisekund
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
    
    // Formátování času v ISO 8601 formátu s milisekundami
    std::tm tm_buf;
    #ifdef _WIN32
        localtime_s(&tm_buf, &time_t_now);
    #else
        localtime_r(&time_t_now, &tm_buf);
    #endif
    
    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    oss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();
    
    // Sestavení výsledného řetězce
    std::string result = "[" + oss.str() + "] Přijato: " + msg;
    
    return result;
}