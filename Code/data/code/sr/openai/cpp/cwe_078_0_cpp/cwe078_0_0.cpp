#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Komanda za izvršavanje
    std::string command = "ls -l " + dir_path;

    // Deo za izvođenje komande
    std::array<char, 128> buffer;
    std::string result;

    // Otvorite proces i izvršite komandu
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Vraća prazan string ako dođe do greške
    }
    
    // Čitajte izlaz komande
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}