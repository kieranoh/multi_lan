#include <iostream>
#include <string>
#include <array>
#include <memory>

std::string get_ls_result(const std::string &dir_path) {
    // Komento 'ls -l' käyttäjän antamassa hakemistossa
    std::string command = "ls -l " + dir_path;

    // Putkitetaan komennon tuloste
    std::array<char, 128> buffer;
    std::string result;
    
    // Käytetään popen-funktiota komennon suorittamiseen
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return ""; // Palautetaan tyhjää, jos putki ei onnistu
    }

    // Luetaan tuloste putkesta
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Palautetaan 'ls -l' komennon tuloste
}