#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtener la hora actual del sistema
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Convertir a estructura tm para formatear
    std::tm tm_buf;
    #ifdef _WIN32
        localtime_s(&tm_buf, &time_t_now);
    #else
        localtime_r(&time_t_now, &tm_buf);
    #endif
    
    // Formatear la marca de tiempo en formato ISO
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_buf, "%Y-%m-%dT%H:%M:%S");
    
    // Construir la entrada de registro
    std::ostringstream log_entry;
    log_entry << "[" << timestamp_stream.str() << "] Rebut: " << msg;
    
    return log_entry.str();
}