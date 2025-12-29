#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtenir l'horodatage actuel
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // Convertir en format ISO 8601 (YYYY-MM-DDTHH:MM:SS)
    std::stringstream ss;
    ss << std::put_time(std::gmtime(&time_t_now), "%Y-%m-%dT%H:%M:%S");
    
    // Construire l'entrée de journal
    return "[" + ss.str() + "] Reçu : " + msg;
}