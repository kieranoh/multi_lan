#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Kreiraj komandu za izvršenje
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Otvori pipe za čitanje izlaza komande
    std::array<char, 128> buffer;
    std::string result;
    
    // Koristimo unique_ptr za automatsko zatvaranje FILE* pokazivača
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Neuspešno otvaranje pipe-a
        return "";
    }
    
    // Pročitaj izlaz komande
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Proveri da li je komanda uspešno izvršena
    // Ako je rezultat prazan, možda je došlo do greške ili je direktorijum prazan
    // Komanda će vratiti prazan string ako ls ne uspe (zbog 2>/dev/null)
    
    return result;
}