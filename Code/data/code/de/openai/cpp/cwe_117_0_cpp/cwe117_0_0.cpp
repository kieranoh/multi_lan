#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Aktuellen Zeitpunkt ermitteln
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Formatieren des Zeitstempels im ISO-Format
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%S");

    // Erzeugen des Protokolleintrags
    return "[" + oss.str() + "] Empfangen: " + msg;
}