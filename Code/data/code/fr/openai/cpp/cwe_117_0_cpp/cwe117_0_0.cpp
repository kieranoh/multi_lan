#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtention de l'heure actuelle
    auto now = std::chrono::system_clock::now();
    std::chrono::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Conversion de l'heure actuelle en format ISO
    std::tm tm = *std::localtime(&now_time);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");

    // Création de l'entrée de journal
    std::string log_entry = "[" + oss.str() + "] Reçu : " + msg;
    return log_entry;
}