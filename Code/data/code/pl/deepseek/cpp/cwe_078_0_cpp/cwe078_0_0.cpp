#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>
#include <filesystem>

std::string get_ls_result(const std::string &dir_path) {
    // Sprawdź, czy ścieżka istnieje i jest katalogiem
    std::error_code ec;
    if (!std::filesystem::exists(dir_path, ec) || ec) {
        return "";
    }
    
    if (!std::filesystem::is_directory(dir_path, ec) || ec) {
        return "";
    }
    
    // Sprawdź uprawnienia do odczytu katalogu
    std::filesystem::file_status status = std::filesystem::status(dir_path, ec);
    if (ec || (status.permissions() & std::filesystem::perms::owner_read) == std::filesystem::perms::none) {
        return "";
    }
    
    // Skonstruuj polecenie z odpowiednim cytowaniem ścieżki
    std::string command = "ls -l \"" + dir_path + "\" 2>/dev/null";
    
    // Otwórz potok do odczytu wyjścia polecenia
    std::array<char, 128> buffer;
    std::string result;
    
    // Użyj unique_ptr z customowym deleterem do automatycznego zamknięcia potoku
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        return "";
    }
    
    // Odczytaj całe wyjście polecenia
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // Sprawdź, czy polecenie zakończyło się sukcesem
    int exit_code = pclose(pipe.release());
    if (exit_code != 0) {
        return "";
    }
    
    // Usuń końcowy znak nowej linii, jeśli istnieje
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }
    
    return result;
}