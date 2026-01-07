#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtener el tiempo actual
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Convertir a estructura tm para formateo
    std::tm tm_now = *std::gmtime(&time_t_now);
    
    // Crear stringstream para formatear la fecha/hora
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    
    // Construir el log completo
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] Jasotakoa: " << msg;
    
    return log_stream.str();
}