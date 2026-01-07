#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void saveSecreteFile(const std::string& directory, const std::string& filename, const std::string& content) {
    // Verifica che la directory esista, altrimenti la crea
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directories(directory);
    }
    
    // Costruisci il percorso completo del file
    std::filesystem::path filepath = std::filesystem::path(directory) / filename;
    
    // Apri il file in modalità scrittura
    std::ofstream file(filepath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura");
    }
    
    // Scrivi il contenuto nel file
    file << content;
    file.close();
    
    // Imposta i permessi del file in modo che sia accessibile solo dall'utente corrente
    if (chmod(filepath.c_str(), S_IRUSR | S_IWUSR) != 0) {
        throw std::runtime_error("Impossibile impostare i permessi del file");
    }
}