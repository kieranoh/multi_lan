#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtenim el temps actual
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    
    // Convertim a format ISO
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_c), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();
    
    // Generem l'entrada de registre
    std::string log_entry = "[" + timestamp + "] Rebut: " + msg;
    return log_entry;
}