#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string generate_receive_log(const std::string &msg) {
    // Získání aktuálního času
    auto now = std::chrono::system_clock::now();
    std::chrono::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    // Formátování časového razítka do ISO formátu
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&now_time), "%Y-%m-%dT%H:%M:%S");
    std::string timestamp = oss.str();
    
    // Vytvoření a vrácení záznamu do protokolu
    return "[" + timestamp + "] Přijato: " + msg;
}