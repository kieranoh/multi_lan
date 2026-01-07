#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtener la marca de tiempo actual
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    // Convertir la marca de tiempo a formato ISO
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();

    // Formar la entrada de registro
    return "[" + timestamp + "] Recibido: " + msg;
}