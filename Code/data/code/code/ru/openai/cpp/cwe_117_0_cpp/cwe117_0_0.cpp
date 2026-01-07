#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>

std::string generate_receive_log(const std::string &msg) {
    // Получаем текущее время
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    // Форматируем метку времени в ISO формате
    std::ostringstream timestamp;
    timestamp << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");

    // Генерируем запись в журнале
    std::ostringstream log_entry;
    log_entry << "[" << timestamp.str() << "] Получено: " << msg;

    return log_entry.str();
}