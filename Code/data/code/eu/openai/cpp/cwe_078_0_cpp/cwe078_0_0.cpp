#include <iostream>
#include <string>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Komandoa osatzen da
    std::string command = "ls -l " + dir_path;

    // Irteera biltegiratzeko arraya
    std::array<char, 128> buffer;
    std::string result;

    // Komandoa exekutatzen da
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        // Hutsik dagoen string bat itzultzen da errore bat egonez gero
        return "";
    }

    // Irteera irakurtzen da
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}