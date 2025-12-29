#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Příkaz pro spuštění
    std::string command = "ls -l " + dir_path;

    // Exekuce příkazu a uchování výstupu
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        return ""; // Vráťte prázdný řetězec v případě chyby
    }

    // Čtení výstupu příkazu
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Vraťte výstup příkazu
}