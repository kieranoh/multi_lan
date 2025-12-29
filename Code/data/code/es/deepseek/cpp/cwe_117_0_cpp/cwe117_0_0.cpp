#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtener la hora actual del sistema
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Convertir a tiempo local
    std::tm tm_now;
    localtime_r(&time_t_now, &tm_now);
    
    // Formatear la marca de tiempo en formato ISO
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    
    // Construir la entrada de registro
    std::ostringstream log_entry;
    log_entry << "[" << timestamp_stream.str() << "] Recibido: " << msg;
    
    return log_entry.str();
}