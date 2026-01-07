#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Hanki nykyinen aikaleima
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    // Muotoile aikaleima ISO-muotoon
    std::ostringstream timestamp;
    timestamp << std::put_time(&now_tm, "%Y-%m-%dT%H:%M:%S");

    // Luo lokimerkintä
    std::ostringstream log_entry;
    log_entry << '[' << timestamp.str() << "] Vastaanotettu: " << msg;

    return log_entry.str();
}