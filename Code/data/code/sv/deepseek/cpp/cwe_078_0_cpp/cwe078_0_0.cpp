#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Konstruera kommandot med explicit katalog
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Öppna en pipe för att läsa kommandots utdata
    std::array<char, 128> buffer;
    std::string result;
    
    // Använd popen för att köra kommandot och läsa stdout
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // Misslyckades med att öppna pipe
        return "";
    }
    
    // Läs utdata från kommandot
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Kontrollera om kommandot kördes framgångsrikt
    // Om resultatet är tomt eller om kommandot misslyckades, returnera tom sträng
    // pclose kommer att returnera kommandots avslutningsstatus
    // Vi använder WEXITSTATUS för att få korrekt avslutningskod
    int status = pclose(pipe.release());
    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        if (exit_code != 0) {
            // Kommandot misslyckades (t.ex. katalog finns inte, behörighetsfel)
            return "";
        }
    } else {
        // Kommandot avslutades abnormalt
        return "";
    }
    
    return result;
}