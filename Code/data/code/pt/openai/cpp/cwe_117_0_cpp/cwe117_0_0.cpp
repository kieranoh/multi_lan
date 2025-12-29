#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Obtendo o timestamp atual
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);
    
    // Formatando o timestamp para o formato ISO
    std::ostringstream oss;
    oss << std::put_time(&tm, "[%Y-%m-%dT%H:%M:%S]");
    
    // Construindo a entrada de log
    std::string log_entry = oss.str() + " Recebido: " + msg;
    return log_entry;
}