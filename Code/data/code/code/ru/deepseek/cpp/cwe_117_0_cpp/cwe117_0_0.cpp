#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Получаем текущее время
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Получаем локальное время
    std::tm local_time = *std::localtime(&time_t_now);
    
    // Форматируем время в ISO формат
    std::ostringstream timestamp_stream;
    timestamp_stream << std::put_time(&local_time, "%Y-%m-%dT%H:%M:%S");
    
    // Создаем запись в журнале
    std::ostringstream log_stream;
    log_stream << "[" << timestamp_stream.str() << "] Получено: " << msg;
    
    return log_stream.str();
}