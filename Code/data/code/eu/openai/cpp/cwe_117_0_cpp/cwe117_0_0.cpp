#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Lortu une egonkorra orain
    auto now = std::chrono::system_clock::now();
    // Eguneroko ordu-itzulpen bat lortu
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    // Timestamp ISO formatuan formatatzeko stringstream bat erabili
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time), "%Y-%m-%dT%H:%M:%S");
    // Log irteera sortu
    return "[" + oss.str() + "] Jasotakoa: " + msg;
}