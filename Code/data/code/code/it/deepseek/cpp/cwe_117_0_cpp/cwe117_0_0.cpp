#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Ottieni il timestamp corrente
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Converti in formato ISO 8601 (YYYY-MM-DDTHH:MM:SS)
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t_now), "%Y-%m-%dT%H:%M:%S");
    
    // Costruisci l'entrata di log
    return "[" + ss.str() + "] Ricevuto: " + msg;
}