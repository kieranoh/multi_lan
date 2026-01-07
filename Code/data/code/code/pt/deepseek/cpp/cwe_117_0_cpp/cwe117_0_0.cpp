#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obter o tempo atual
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Converter para tm para formatação
    std::tm tm_now;
    #ifdef _WIN32
        localtime_s(&tm_now, &time_t_now);
    #else
        localtime_r(&time_t_now, &tm_now);
    #endif
    
    // Formatar o timestamp no formato ISO
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&tm_now, "%Y-%m-%dT%H:%M:%S");
    
    // Construir a string de log
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] Recebido: " << msg;
    
    return log_stream.str();
}