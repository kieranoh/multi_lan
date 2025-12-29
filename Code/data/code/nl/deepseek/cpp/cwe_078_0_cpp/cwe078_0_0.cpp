#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Bouw het commando met het opgegeven pad
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Open een pipe om de uitvoer van het commando te lezen
    std::array<char, 128> buffer;
    std::string result;
    
    // Gebruik popen om het commando uit te voeren en de uitvoer te lezen
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Als popen faalt, retourneer een lege string
        return "";
    }
    
    // Lees de uitvoer van het commando
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Verwijder eventuele trailing newline voor consistentie
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}