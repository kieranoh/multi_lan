#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

std::string generate_receive_log(const std::string &msg) {
    // Ottieni il timestamp attuale
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    
    // Converte il timestamp in formato ISO 8601
    std::tm *tm = std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(tm, "[%Y-%m-%dT%H:%M:%S]");
    
    // Crea l'entrata di log
    return oss.str() + " Ricevuto: " + msg;
}