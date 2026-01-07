#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>

std::string get_ls_result(const std::string &dir_path) {
    // Konstruiere den Befehl mit dem angegebenen Verzeichnispfad
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Öffne einen Pipe zum Lesen der Ausgabe des Befehls
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    // Überprüfe, ob der Pipe erfolgreich geöffnet wurde
    if (!pipe) {
        return "";
    }
    
    // Lese die Ausgabe des Befehls
    std::array<char, 128> buffer;
    std::string result;
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Entferne mögliche abschließende Newline-Zeichen
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }
    
    return result;
}