#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Tworzymy pełną ścieżkę do pliku
    std::filesystem::path filePath = std::filesystem::path(directory) / filename;

    // Tworzymy i zapisujemy treść do pliku
    std::ofstream outFile(filePath);
    if (outFile) {
        outFile << content;
        outFile.close();
        
        // Ustawiamy prawa dostępu do pliku, aby był dostępny tylko dla bieżącego użytkownika
        chmod(filePath.c_str(), S_IRUSR | S_IWUSR);
    } else {
        std::cerr << "Błąd podczas otwierania pliku do zapisu." << std::endl;
    }
}