#include <iostream>
#include <string>
#include <memory>
#include <array>

std::string get_ls_result(const std::string &dir_path) {
    // Komanda koju želimo izvršiti
    std::string command = "ls -l " + dir_path;

    // Otvoriti cijev za povratni izlaz
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // Provjeriti da li je cijev otvorena
    if (!pipe) {
        return ""; // Vratiti prazan niz u slučaju greške
    }

    // Čitati izlaz iz cijevi
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result; // Vratiti rezultat
}